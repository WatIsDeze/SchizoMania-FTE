/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* voice sentence samples for AI and other triggers that are supposed to talk.
 * the formatting is messy as hell and I feel dirty for even bothering with all
 * this to begin with.
 * 
 * the server will send a short string identifer over and we'll look it up.
 * what's annoying is that some NPCs got their own pitch overrides so I guess
 * we'll just default to those whenever there's no custom value set.
 */

/* sentences are the voice-acting backbone of the sound system.
 * http://articles.thewavelength.net/230/
 * has pretty good documentation of how the format is meant to work */

/* Sentences Documentation

	Each line is a new sentence group.
    [GROUPNAME] [...PARAMETERS] [...SAMPLES]

    If a sample is not in a sub-directory, it'll be assumed to be part
    of the 'vox' sub-directory, or the last valid path of a previous sample.
    For example
        attention male/hello how are you
    becomes
        vox/attention.wav male/hello.wav male/how.wav male/are.wav male/you.wav

	When parameters are surrounded by spaces, this means they apply
    to all current samples. They can be overwritten later down the parsing.
    When a parameter is attached to a sample, e.g.
        attention(p120)
    Then this parameter only applies to said keyword.
    Whereas...
        (p120) attention everyone alive
    Will apply the pitch effect to all three succeeding samples.

	Parameters:
    (pXX) = Pitch. Valid values are from 50 to 150.
    (vXX) = Volume. Valid values are from 0 to 100.
    (sXX) = Start point in %. E.g. 10 skips the first 10% of the sample.
    (eXX) = End point in %. E.g. 75 ends playback 75% into the sample.
    (tXX) = Time shift/compression in %. 100 is unaltered speed,
            wheras 50 plays the sample back in half the time.
*/

/* enable this if you want to use memalloc */
#define DYNAMIC_SENTENCES

typedef struct
{
	string m_strID;
	string m_strSamples;
} sentences_t;

#ifdef DYNAMIC_SENTENCES
	sentences_t *g_sentences;
	int g_sentences_count;
#else
	#define SENTENCES_LIMIT 1024
	sentences_t g_sentences[SENTENCES_LIMIT];
	int g_sentences_count;
#endif

var string g_sentences_samplepath;

void
Sentences_Init(void)
{
	filestream fs_sentences;
	string temp;
	int c, i;

	if (g_sentences_count > 0) {
		g_sentences_count = 0;

#ifndef DYNAMIC_SENTENCES
		if (g_sentences) {
			memfree(g_sentences);
		}
#endif
	}

	fs_sentences = fopen("sound/sentences.txt", FILE_READ);

	if (fs_sentences < 0) {
		print("^1WARNING: ^7Could NOT load sound/sentences.txt\n");
		return;
	}

	while ((temp = fgets(fs_sentences))) {
		/* tons of comments/garbage in those files,
		 * so tokenize appropriately */
		c = tokenize_console(temp);

		/* not enough for an entry. */
		if (c < 2) {
			continue;
		}

		/* starts of at 0, for every line increases */
		int x = g_sentences_count;

		/* allocate memory and increase count */
#ifdef DYNAMIC_SENTENCES
		g_sentences_count++;
		g_sentences = memrealloc(g_sentences,
				sizeof(sentences_t),
				x,
				g_sentences_count);
#else
		if (g_sentences_count + 1 >= SENTENCES_LIMIT) {
			print("^1WARNING: ^7Reached limit of max sentences!\n");
			return;
		}

		g_sentences_count++;
#endif

		/* loop through the parts of the line */
		for (i=0; i < c; i++) {
			/* first entry is the id, prefix with ! as well */
			if (i==0) {
				g_sentences[x].m_strID = strtoupper(strcat("!", argv(0)));
			} else {
				if (i == 1) {
					g_sentences[x].m_strSamples = sprintf("%s", argv(i));
				} else {
					g_sentences[x].m_strSamples = sprintf("%s %s", g_sentences[x].m_strSamples, argv(i));
				}

				g_sentences[x].m_strSamples = 
					strreplace(",", " vox/comma.wav", g_sentences[x].m_strSamples);
			}
		}
	}
}

string
Sentences_ProcessSample(string sample)
{
	int c = tokenizebyseparator(sample, "/");

	/* this sample contains a path */
	if (c > 1) {
		g_sentences_samplepath = argv(0);
		return sample;
	}

	/* we don't have a path, so supply the default */
	return sprintf("%s/%s", g_sentences_samplepath, argv(0));
}

void
Sentences_ResetSample(void)
{
	g_sentences_samplepath = "vox";
}

string
Sentences_GetSamples(string msg)
{
	Sentences_ResetSample();

	for (int i = 0; i < g_sentences_count; i++) {
		if (g_sentences[i].m_strID == msg) {
			return g_sentences[i].m_strSamples;
		}
	}
	return "";
}
