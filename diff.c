#include "object-store.h"
#include "hashmap.h"
#include "packfile.h"
#include "parse-options.h"
#include "help.h"
#include "promisor-remote.h"
static int diff_color_moved_default;
static int diff_color_moved_ws_default;
	GIT_COLOR_BOLD_MAGENTA,	/* OLD_MOVED */
	GIT_COLOR_BOLD_BLUE,	/* OLD_MOVED ALTERNATIVE */
	GIT_COLOR_FAINT,	/* OLD_MOVED_DIM */
	GIT_COLOR_FAINT_ITALIC,	/* OLD_MOVED_ALTERNATIVE_DIM */
	GIT_COLOR_BOLD_CYAN,	/* NEW_MOVED */
	GIT_COLOR_BOLD_YELLOW,	/* NEW_MOVED ALTERNATIVE */
	GIT_COLOR_FAINT,	/* NEW_MOVED_DIM */
	GIT_COLOR_FAINT_ITALIC,	/* NEW_MOVED_ALTERNATIVE_DIM */
	GIT_COLOR_FAINT,	/* CONTEXT_DIM */
	GIT_COLOR_FAINT_RED,	/* OLD_DIM */
	GIT_COLOR_FAINT_GREEN,	/* NEW_DIM */
	GIT_COLOR_BOLD,		/* CONTEXT_BOLD */
	GIT_COLOR_BOLD_RED,	/* OLD_BOLD */
	GIT_COLOR_BOLD_GREEN,	/* NEW_BOLD */
static const char *color_diff_slots[] = {
	[DIFF_CONTEXT]		      = "context",
	[DIFF_METAINFO]		      = "meta",
	[DIFF_FRAGINFO]		      = "frag",
	[DIFF_FILE_OLD]		      = "old",
	[DIFF_FILE_NEW]		      = "new",
	[DIFF_COMMIT]		      = "commit",
	[DIFF_WHITESPACE]	      = "whitespace",
	[DIFF_FUNCINFO]		      = "func",
	[DIFF_FILE_OLD_MOVED]	      = "oldMoved",
	[DIFF_FILE_OLD_MOVED_ALT]     = "oldMovedAlternative",
	[DIFF_FILE_OLD_MOVED_DIM]     = "oldMovedDimmed",
	[DIFF_FILE_OLD_MOVED_ALT_DIM] = "oldMovedAlternativeDimmed",
	[DIFF_FILE_NEW_MOVED]	      = "newMoved",
	[DIFF_FILE_NEW_MOVED_ALT]     = "newMovedAlternative",
	[DIFF_FILE_NEW_MOVED_DIM]     = "newMovedDimmed",
	[DIFF_FILE_NEW_MOVED_ALT_DIM] = "newMovedAlternativeDimmed",
	[DIFF_CONTEXT_DIM]	      = "contextDimmed",
	[DIFF_FILE_OLD_DIM]	      = "oldDimmed",
	[DIFF_FILE_NEW_DIM]	      = "newDimmed",
	[DIFF_CONTEXT_BOLD]	      = "contextBold",
	[DIFF_FILE_OLD_BOLD]	      = "oldBold",
	[DIFF_FILE_NEW_BOLD]	      = "newBold",
};

define_list_config_array_extra(color_diff_slots, {"plain"});
	if (!strcasecmp(var, "plain"))
	return LOOKUP_CONFIG(color_diff_slots, var);
			options->flags.dirstat_by_line = 0;
			options->flags.dirstat_by_file = 0;
			options->flags.dirstat_by_line = 1;
			options->flags.dirstat_by_file = 0;
			options->flags.dirstat_by_line = 0;
			options->flags.dirstat_by_file = 1;
			options->flags.dirstat_cumulative = 0;
			options->flags.dirstat_cumulative = 1;
	/*
	 * Please update $__git_diff_submodule_formats in
	 * git-completion.bash when you add new formats.
	 */
int git_config_rename(const char *var, const char *value)
	/*
	 * Please update $__git_diff_algorithms in git-completion.bash
	 * when you add new algorithms.
	 */
	diff_detect_rename_default = DIFF_DETECT_RENAME;
static int parse_color_moved(const char *arg)
{
	switch (git_parse_maybe_bool(arg)) {
	case 0:
		return COLOR_MOVED_NO;
	case 1:
		return COLOR_MOVED_DEFAULT;
	default:
		break;
	}

	if (!strcmp(arg, "no"))
		return COLOR_MOVED_NO;
	else if (!strcmp(arg, "plain"))
		return COLOR_MOVED_PLAIN;
	else if (!strcmp(arg, "blocks"))
		return COLOR_MOVED_BLOCKS;
	else if (!strcmp(arg, "zebra"))
		return COLOR_MOVED_ZEBRA;
	else if (!strcmp(arg, "default"))
		return COLOR_MOVED_DEFAULT;
	else if (!strcmp(arg, "dimmed-zebra"))
		return COLOR_MOVED_ZEBRA_DIM;
	else if (!strcmp(arg, "dimmed_zebra"))
		return COLOR_MOVED_ZEBRA_DIM;
	else
		return error(_("color moved setting must be one of 'no', 'default', 'blocks', 'zebra', 'dimmed-zebra', 'plain'"));
}

static unsigned parse_color_moved_ws(const char *arg)
{
	int ret = 0;
	struct string_list l = STRING_LIST_INIT_DUP;
	struct string_list_item *i;

	string_list_split(&l, arg, ',', -1);

	for_each_string_list_item(i, &l) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addstr(&sb, i->string);
		strbuf_trim(&sb);

		if (!strcmp(sb.buf, "no"))
			ret = 0;
		else if (!strcmp(sb.buf, "ignore-space-change"))
			ret |= XDF_IGNORE_WHITESPACE_CHANGE;
		else if (!strcmp(sb.buf, "ignore-space-at-eol"))
			ret |= XDF_IGNORE_WHITESPACE_AT_EOL;
		else if (!strcmp(sb.buf, "ignore-all-space"))
			ret |= XDF_IGNORE_WHITESPACE;
		else if (!strcmp(sb.buf, "allow-indentation-change"))
			ret |= COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE;
		else {
			ret |= COLOR_MOVED_WS_ERROR;
			error(_("unknown color-moved-ws mode '%s', possible values are 'ignore-space-change', 'ignore-space-at-eol', 'ignore-all-space', 'allow-indentation-change'"), sb.buf);
		}

		strbuf_release(&sb);
	}

	if ((ret & COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE) &&
	    (ret & XDF_WHITESPACE_FLAGS)) {
		error(_("color-moved-ws: allow-indentation-change cannot be combined with other whitespace modes"));
		ret |= COLOR_MOVED_WS_ERROR;
	}

	string_list_clear(&l, 0);

	return ret;
}

	if (!strcmp(var, "diff.colormoved")) {
		int cm = parse_color_moved(value);
		if (cm < 0)
			return -1;
		diff_color_moved_default = cm;
		return 0;
	}
	if (!strcmp(var, "diff.colormovedws")) {
		unsigned cm = parse_color_moved_ws(value);
		if (cm & COLOR_MOVED_WS_ERROR)
			return -1;
		diff_color_moved_ws_default = cm;
		return 0;
	}
	if (!strcmp(var, "diff.wserrorhighlight")) {
		int val = parse_ws_error_highlight(value);
		if (val < 0)
			return -1;
		ws_error_highlight_default = val;
		return 0;
	}

	external_diff_cmd = xstrdup_or_null(getenv("GIT_EXTERNAL_DIFF"));
	struct tempfile *tempfile;
static int fill_mmfile(struct repository *r, mmfile_t *mf,
		       struct diff_filespec *one)
	else if (diff_populate_filespec(r, one, 0))
static unsigned long diff_filespec_size(struct repository *r,
					struct diff_filespec *one)
	diff_populate_filespec(r, one, CHECK_SIZE_ONLY);
static void emit_line_0(struct diff_options *o,
			const char *set_sign, const char *set, unsigned reverse, const char *reset,
	int needs_reset = 0; /* at the end of the line */
	has_trailing_newline = (len > 0 && line[len-1] == '\n');
	if (has_trailing_newline)
		len--;

	has_trailing_carriage_return = (len > 0 && line[len-1] == '\r');
	if (has_trailing_carriage_return)
		len--;

	if (!len && !first)
		goto end_of_line;

	if (reverse && want_color(o->use_color)) {
		fputs(GIT_COLOR_REVERSE, file);
		needs_reset = 1;
	}

	if (set_sign) {
		fputs(set_sign, file);
		needs_reset = 1;
	if (first)
		fputc(first, file);

	if (!len)
		goto end_of_line;

	if (set) {
		if (set_sign && set != set_sign)
			fputs(reset, file);
		needs_reset = 1;
	fwrite(line, len, 1, file);
	needs_reset = 1; /* 'line' may contain color codes. */

end_of_line:
	if (needs_reset)
		fputs(reset, file);
	emit_line_0(o, set, NULL, 0, reset, 0, line, len);
}

enum diff_symbol {
	DIFF_SYMBOL_BINARY_DIFF_HEADER,
	DIFF_SYMBOL_BINARY_DIFF_HEADER_DELTA,
	DIFF_SYMBOL_BINARY_DIFF_HEADER_LITERAL,
	DIFF_SYMBOL_BINARY_DIFF_BODY,
	DIFF_SYMBOL_BINARY_DIFF_FOOTER,
	DIFF_SYMBOL_STATS_SUMMARY_NO_FILES,
	DIFF_SYMBOL_STATS_SUMMARY_ABBREV,
	DIFF_SYMBOL_STATS_SUMMARY_INSERTS_DELETES,
	DIFF_SYMBOL_STATS_LINE,
	DIFF_SYMBOL_WORD_DIFF,
	DIFF_SYMBOL_STAT_SEP,
	DIFF_SYMBOL_SUMMARY,
	DIFF_SYMBOL_SUBMODULE_ADD,
	DIFF_SYMBOL_SUBMODULE_DEL,
	DIFF_SYMBOL_SUBMODULE_UNTRACKED,
	DIFF_SYMBOL_SUBMODULE_MODIFIED,
	DIFF_SYMBOL_SUBMODULE_HEADER,
	DIFF_SYMBOL_SUBMODULE_ERROR,
	DIFF_SYMBOL_SUBMODULE_PIPETHROUGH,
	DIFF_SYMBOL_REWRITE_DIFF,
	DIFF_SYMBOL_BINARY_FILES,
	DIFF_SYMBOL_HEADER,
	DIFF_SYMBOL_FILEPAIR_PLUS,
	DIFF_SYMBOL_FILEPAIR_MINUS,
	DIFF_SYMBOL_WORDS_PORCELAIN,
	DIFF_SYMBOL_WORDS,
	DIFF_SYMBOL_CONTEXT,
	DIFF_SYMBOL_CONTEXT_INCOMPLETE,
	DIFF_SYMBOL_PLUS,
	DIFF_SYMBOL_MINUS,
	DIFF_SYMBOL_NO_LF_EOF,
	DIFF_SYMBOL_CONTEXT_FRAGINFO,
	DIFF_SYMBOL_CONTEXT_MARKER,
	DIFF_SYMBOL_SEPARATOR
};
/*
 * Flags for content lines:
 * 0..12 are whitespace rules
 * 13-15 are WSEH_NEW | WSEH_OLD | WSEH_CONTEXT
 * 16 is marking if the line is blank at EOF
 */
#define DIFF_SYMBOL_CONTENT_BLANK_LINE_EOF	(1<<16)
#define DIFF_SYMBOL_MOVED_LINE			(1<<17)
#define DIFF_SYMBOL_MOVED_LINE_ALT		(1<<18)
#define DIFF_SYMBOL_MOVED_LINE_UNINTERESTING	(1<<19)
#define DIFF_SYMBOL_CONTENT_WS_MASK (WSEH_NEW | WSEH_OLD | WSEH_CONTEXT | WS_RULE_MASK)

/*
 * This struct is used when we need to buffer the output of the diff output.
 *
 * NEEDSWORK: Instead of storing a copy of the line, add an offset pointer
 * into the pre/post image file. This pointer could be a union with the
 * line pointer. By storing an offset into the file instead of the literal line,
 * we can decrease the memory footprint for the buffered output. At first we
 * may want to only have indirection for the content lines, but we could also
 * enhance the state for emitting prefabricated lines, e.g. the similarity
 * score line or hunk/file headers would only need to store a number or path
 * and then the output can be constructed later on depending on state.
 */
struct emitted_diff_symbol {
	const char *line;
	int len;
	int flags;
	int indent_off;   /* Offset to first non-whitespace character */
	int indent_width; /* The visual width of the indentation */
	enum diff_symbol s;
};
#define EMITTED_DIFF_SYMBOL_INIT {NULL}

struct emitted_diff_symbols {
	struct emitted_diff_symbol *buf;
	int nr, alloc;
};
#define EMITTED_DIFF_SYMBOLS_INIT {NULL, 0, 0}

static void append_emitted_diff_symbol(struct diff_options *o,
				       struct emitted_diff_symbol *e)
{
	struct emitted_diff_symbol *f;

	ALLOC_GROW(o->emitted_symbols->buf,
		   o->emitted_symbols->nr + 1,
		   o->emitted_symbols->alloc);
	f = &o->emitted_symbols->buf[o->emitted_symbols->nr++];

	memcpy(f, e, sizeof(struct emitted_diff_symbol));
	f->line = e->line ? xmemdupz(e->line, e->len) : NULL;
struct moved_entry {
	struct hashmap_entry ent;
	const struct emitted_diff_symbol *es;
	struct moved_entry *next_line;
};

struct moved_block {
	struct moved_entry *match;
	int wsd; /* The whitespace delta of this block */
};

static void moved_block_clear(struct moved_block *b)
	memset(b, 0, sizeof(*b));
}

#define INDENT_BLANKLINE INT_MIN

static void fill_es_indent_data(struct emitted_diff_symbol *es)
{
	unsigned int off = 0, i;
	int width = 0, tab_width = es->flags & WS_TAB_WIDTH_MASK;
	const char *s = es->line;
	const int len = es->len;

	/* skip any \v \f \r at start of indentation */
	while (s[off] == '\f' || s[off] == '\v' ||
	       (s[off] == '\r' && off < len - 1))
		off++;

	/* calculate the visual width of indentation */
	while(1) {
		if (s[off] == ' ') {
			width++;
			off++;
		} else if (s[off] == '\t') {
			width += tab_width - (width % tab_width);
			while (s[++off] == '\t')
				width += tab_width;
		} else {
			break;
		}
	}

	/* check if this line is blank */
	for (i = off; i < len; i++)
		if (!isspace(s[i]))
		    break;

	if (i == len) {
		es->indent_width = INDENT_BLANKLINE;
		es->indent_off = len;
	} else {
		es->indent_off = off;
		es->indent_width = width;
	}
}

static int compute_ws_delta(const struct emitted_diff_symbol *a,
			    const struct emitted_diff_symbol *b,
			    int *out)
{
	int a_len = a->len,
	    b_len = b->len,
	    a_off = a->indent_off,
	    a_width = a->indent_width,
	    b_off = b->indent_off,
	    b_width = b->indent_width;
	int delta;

	if (a_width == INDENT_BLANKLINE && b_width == INDENT_BLANKLINE) {
		*out = INDENT_BLANKLINE;
		return 1;
	}

	if (a->s == DIFF_SYMBOL_PLUS)
		delta = a_width - b_width;
	else
		delta = b_width - a_width;

	if (a_len - a_off != b_len - b_off ||
	    memcmp(a->line + a_off, b->line + b_off, a_len - a_off))

	*out = delta;

	return 1;
}

static int cmp_in_block_with_wsd(const struct diff_options *o,
				 const struct moved_entry *cur,
				 const struct moved_entry *match,
				 struct moved_block *pmb,
				 int n)
{
	struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
	int al = cur->es->len, bl = match->es->len, cl = l->len;
	const char *a = cur->es->line,
		   *b = match->es->line,
		   *c = l->line;
	int a_off = cur->es->indent_off,
	    a_width = cur->es->indent_width,
	    c_off = l->indent_off,
	    c_width = l->indent_width;
	int delta;

	/*
	 * We need to check if 'cur' is equal to 'match'.  As those
	 * are from the same (+/-) side, we do not need to adjust for
	 * indent changes. However these were found using fuzzy
	 * matching so we do have to check if they are equal. Here we
	 * just check the lengths. We delay calling memcmp() to check
	 * the contents until later as if the length comparison for a
	 * and c fails we can avoid the call all together.
	 */
	if (al != bl)
		return 1;

	/* If 'l' and 'cur' are both blank then they match. */
	if (a_width == INDENT_BLANKLINE && c_width == INDENT_BLANKLINE)
		return 0;

	/*
	 * The indent changes of the block are known and stored in pmb->wsd;
	 * however we need to check if the indent changes of the current line
	 * match those of the current block and that the text of 'l' and 'cur'
	 * after the indentation match.
	 */
	if (cur->es->s == DIFF_SYMBOL_PLUS)
		delta = a_width - c_width;
	else
		delta = c_width - a_width;

	/*
	 * If the previous lines of this block were all blank then set its
	 * whitespace delta.
	 */
	if (pmb->wsd == INDENT_BLANKLINE)
		pmb->wsd = delta;

	return !(delta == pmb->wsd && al - a_off == cl - c_off &&
		 !memcmp(a, b, al) && !
		 memcmp(a + a_off, c + c_off, al - a_off));
}

static int moved_entry_cmp(const void *hashmap_cmp_fn_data,
			   const struct hashmap_entry *eptr,
			   const struct hashmap_entry *entry_or_key,
			   const void *keydata)
{
	const struct diff_options *diffopt = hashmap_cmp_fn_data;
	const struct moved_entry *a, *b;
	unsigned flags = diffopt->color_moved_ws_handling
			 & XDF_WHITESPACE_FLAGS;

	a = container_of(eptr, const struct moved_entry, ent);
	b = container_of(entry_or_key, const struct moved_entry, ent);

	if (diffopt->color_moved_ws_handling &
	    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
		/*
		 * As there is not specific white space config given,
		 * we'd need to check for a new block, so ignore all
		 * white space. The setup of the white space
		 * configuration for the next block is done else where
		 */
		flags |= XDF_IGNORE_WHITESPACE;

	return !xdiff_compare_lines(a->es->line, a->es->len,
				    b->es->line, b->es->len,
				    flags);
}

static struct moved_entry *prepare_entry(struct diff_options *o,
					 int line_no)
{
	struct moved_entry *ret = xmalloc(sizeof(*ret));
	struct emitted_diff_symbol *l = &o->emitted_symbols->buf[line_no];
	unsigned flags = o->color_moved_ws_handling & XDF_WHITESPACE_FLAGS;
	unsigned int hash = xdiff_hash_string(l->line, l->len, flags);

	hashmap_entry_init(&ret->ent, hash);
	ret->es = l;
	ret->next_line = NULL;

	return ret;
}

static void add_lines_to_move_detection(struct diff_options *o,
					struct hashmap *add_lines,
					struct hashmap *del_lines)
{
	struct moved_entry *prev_line = NULL;

	int n;
	for (n = 0; n < o->emitted_symbols->nr; n++) {
		struct hashmap *hm;
		struct moved_entry *key;

		switch (o->emitted_symbols->buf[n].s) {
		case DIFF_SYMBOL_PLUS:
			hm = add_lines;
			break;
		case DIFF_SYMBOL_MINUS:
			hm = del_lines;
			break;
		default:
			prev_line = NULL;
			continue;
		}

		if (o->color_moved_ws_handling &
		    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
			fill_es_indent_data(&o->emitted_symbols->buf[n]);
		key = prepare_entry(o, n);
		if (prev_line && prev_line->es->s == o->emitted_symbols->buf[n].s)
			prev_line->next_line = key;

		hashmap_add(hm, &key->ent);
		prev_line = key;
	}
}

static void pmb_advance_or_null(struct diff_options *o,
				struct moved_entry *match,
				struct hashmap *hm,
				struct moved_block *pmb,
				int pmb_nr)
{
	int i;
	for (i = 0; i < pmb_nr; i++) {
		struct moved_entry *prev = pmb[i].match;
		struct moved_entry *cur = (prev && prev->next_line) ?
				prev->next_line : NULL;
		if (cur && !hm->cmpfn(o, &cur->ent, &match->ent, NULL)) {
			pmb[i].match = cur;
		} else {
			pmb[i].match = NULL;
		}
	}
}

static void pmb_advance_or_null_multi_match(struct diff_options *o,
					    struct moved_entry *match,
					    struct hashmap *hm,
					    struct moved_block *pmb,
					    int pmb_nr, int n)
{
	int i;
	char *got_match = xcalloc(1, pmb_nr);

	hashmap_for_each_entry_from(hm, match, ent) {
		for (i = 0; i < pmb_nr; i++) {
			struct moved_entry *prev = pmb[i].match;
			struct moved_entry *cur = (prev && prev->next_line) ?
					prev->next_line : NULL;
			if (!cur)
				continue;
			if (!cmp_in_block_with_wsd(o, cur, match, &pmb[i], n))
				got_match[i] |= 1;
		}
	}

	for (i = 0; i < pmb_nr; i++) {
		if (got_match[i]) {
			/* Advance to the next line */
			pmb[i].match = pmb[i].match->next_line;
		} else {
			moved_block_clear(&pmb[i]);
		}
	}

	free(got_match);
}

static int shrink_potential_moved_blocks(struct moved_block *pmb,
					 int pmb_nr)
{
	int lp, rp;

	/* Shrink the set of potential block to the remaining running */
	for (lp = 0, rp = pmb_nr - 1; lp <= rp;) {
		while (lp < pmb_nr && pmb[lp].match)
			lp++;
		/* lp points at the first NULL now */

		while (rp > -1 && !pmb[rp].match)
			rp--;
		/* rp points at the last non-NULL */

		if (lp < pmb_nr && rp > -1 && lp < rp) {
			pmb[lp] = pmb[rp];
			memset(&pmb[rp], 0, sizeof(pmb[rp]));
			rp--;
			lp++;
		}
	}

	/* Remember the number of running sets */
	return rp + 1;
}

/*
 * If o->color_moved is COLOR_MOVED_PLAIN, this function does nothing.
 *
 * Otherwise, if the last block has fewer alphanumeric characters than
 * COLOR_MOVED_MIN_ALNUM_COUNT, unset DIFF_SYMBOL_MOVED_LINE on all lines in
 * that block.
 *
 * The last block consists of the (n - block_length)'th line up to but not
 * including the nth line.
 *
 * Returns 0 if the last block is empty or is unset by this function, non zero
 * otherwise.
 *
 * NEEDSWORK: This uses the same heuristic as blame_entry_score() in blame.c.
 * Think of a way to unify them.
 */
static int adjust_last_block(struct diff_options *o, int n, int block_length)
{
	int i, alnum_count = 0;
	if (o->color_moved == COLOR_MOVED_PLAIN)
		return block_length;
	for (i = 1; i < block_length + 1; i++) {
		const char *c = o->emitted_symbols->buf[n - i].line;
		for (; *c; c++) {
			if (!isalnum(*c))
				continue;
			alnum_count++;
			if (alnum_count >= COLOR_MOVED_MIN_ALNUM_COUNT)
				return 1;
		}
	}
	for (i = 1; i < block_length + 1; i++)
		o->emitted_symbols->buf[n - i].flags &= ~DIFF_SYMBOL_MOVED_LINE;
	return 0;
}

/* Find blocks of moved code, delegate actual coloring decision to helper */
static void mark_color_as_moved(struct diff_options *o,
				struct hashmap *add_lines,
				struct hashmap *del_lines)
{
	struct moved_block *pmb = NULL; /* potentially moved blocks */
	int pmb_nr = 0, pmb_alloc = 0;
	int n, flipped_block = 0, block_length = 0;


	for (n = 0; n < o->emitted_symbols->nr; n++) {
		struct hashmap *hm = NULL;
		struct moved_entry *key;
		struct moved_entry *match = NULL;
		struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
		enum diff_symbol last_symbol = 0;

		switch (l->s) {
		case DIFF_SYMBOL_PLUS:
			hm = del_lines;
			key = prepare_entry(o, n);
			match = hashmap_get_entry(hm, key, ent, NULL);
			free(key);
			break;
		case DIFF_SYMBOL_MINUS:
			hm = add_lines;
			key = prepare_entry(o, n);
			match = hashmap_get_entry(hm, key, ent, NULL);
			free(key);
			break;
		default:
			flipped_block = 0;
		}

		if (!match) {
			int i;

			adjust_last_block(o, n, block_length);
			for(i = 0; i < pmb_nr; i++)
				moved_block_clear(&pmb[i]);
			pmb_nr = 0;
			block_length = 0;
			flipped_block = 0;
			last_symbol = l->s;
			continue;
		}

		if (o->color_moved == COLOR_MOVED_PLAIN) {
			last_symbol = l->s;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
			continue;
		}

		if (o->color_moved_ws_handling &
		    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
			pmb_advance_or_null_multi_match(o, match, hm, pmb, pmb_nr, n);
		else
			pmb_advance_or_null(o, match, hm, pmb, pmb_nr);

		pmb_nr = shrink_potential_moved_blocks(pmb, pmb_nr);

		if (pmb_nr == 0) {
			/*
			 * The current line is the start of a new block.
			 * Setup the set of potential blocks.
			 */
			hashmap_for_each_entry_from(hm, match, ent) {
				ALLOC_GROW(pmb, pmb_nr + 1, pmb_alloc);
				if (o->color_moved_ws_handling &
				    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE) {
					if (compute_ws_delta(l, match->es,
							     &pmb[pmb_nr].wsd))
						pmb[pmb_nr++].match = match;
				} else {
					pmb[pmb_nr].wsd = 0;
					pmb[pmb_nr++].match = match;
				}
			}

			if (adjust_last_block(o, n, block_length) &&
			    pmb_nr && last_symbol != l->s)
				flipped_block = (flipped_block + 1) % 2;
			else
				flipped_block = 0;

			block_length = 0;
		}

		if (pmb_nr) {
			block_length++;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
			if (flipped_block && o->color_moved != COLOR_MOVED_BLOCKS)
				l->flags |= DIFF_SYMBOL_MOVED_LINE_ALT;
		}
		last_symbol = l->s;
	}
	adjust_last_block(o, n, block_length);

	for(n = 0; n < pmb_nr; n++)
		moved_block_clear(&pmb[n]);
	free(pmb);
}

#define DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK \
  (DIFF_SYMBOL_MOVED_LINE | DIFF_SYMBOL_MOVED_LINE_ALT)
static void dim_moved_lines(struct diff_options *o)
{
	int n;
	for (n = 0; n < o->emitted_symbols->nr; n++) {
		struct emitted_diff_symbol *prev = (n != 0) ?
				&o->emitted_symbols->buf[n - 1] : NULL;
		struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
		struct emitted_diff_symbol *next =
				(n < o->emitted_symbols->nr - 1) ?
				&o->emitted_symbols->buf[n + 1] : NULL;

		/* Not a plus or minus line? */
		if (l->s != DIFF_SYMBOL_PLUS && l->s != DIFF_SYMBOL_MINUS)
			continue;

		/* Not a moved line? */
		if (!(l->flags & DIFF_SYMBOL_MOVED_LINE))
			continue;

		/*
		 * If prev or next are not a plus or minus line,
		 * pretend they don't exist
		 */
		if (prev && prev->s != DIFF_SYMBOL_PLUS &&
			    prev->s != DIFF_SYMBOL_MINUS)
			prev = NULL;
		if (next && next->s != DIFF_SYMBOL_PLUS &&
			    next->s != DIFF_SYMBOL_MINUS)
			next = NULL;

		/* Inside a block? */
		if ((prev &&
		    (prev->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK) ==
		    (l->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK)) &&
		    (next &&
		    (next->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK) ==
		    (l->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK))) {
			l->flags |= DIFF_SYMBOL_MOVED_LINE_UNINTERESTING;
			continue;
		}

		/* Check if we are at an interesting bound: */
		if (prev && (prev->flags & DIFF_SYMBOL_MOVED_LINE) &&
		    (prev->flags & DIFF_SYMBOL_MOVED_LINE_ALT) !=
		       (l->flags & DIFF_SYMBOL_MOVED_LINE_ALT))
			continue;
		if (next && (next->flags & DIFF_SYMBOL_MOVED_LINE) &&
		    (next->flags & DIFF_SYMBOL_MOVED_LINE_ALT) !=
		       (l->flags & DIFF_SYMBOL_MOVED_LINE_ALT))
			continue;

		/*
		 * The boundary to prev and next are not interesting,
		 * so this line is not interesting as a whole
		 */
		l->flags |= DIFF_SYMBOL_MOVED_LINE_UNINTERESTING;
	}
static void emit_line_ws_markup(struct diff_options *o,
				const char *set_sign, const char *set,
				const char *reset,
				int sign_index, const char *line, int len,
				unsigned ws_rule, int blank_at_eof)
	int sign = o->output_indicators[sign_index];
	if (o->ws_error_highlight & ws_rule) {
		ws = diff_get_color_opt(o, DIFF_WHITESPACE);
	if (!ws && !set_sign)
		emit_line_0(o, set, NULL, 0, reset, sign, line, len);
	else if (!ws) {
		emit_line_0(o, set_sign, set, !!set_sign, reset, sign, line, len);
	} else if (blank_at_eof)
		emit_line_0(o, ws, NULL, 0, reset, sign, line, len);
		emit_line_0(o, set_sign ? set_sign : set, NULL, !!set_sign, reset,
			    sign, "", 0);
		ws_check_emit(line, len, ws_rule,
			      o->file, set, reset, ws);
static void emit_diff_symbol_from_struct(struct diff_options *o,
					 struct emitted_diff_symbol *eds)
{
	static const char *nneof = " No newline at end of file\n";
	const char *context, *reset, *set, *set_sign, *meta, *fraginfo;
	struct strbuf sb = STRBUF_INIT;

	enum diff_symbol s = eds->s;
	const char *line = eds->line;
	int len = eds->len;
	unsigned flags = eds->flags;

	switch (s) {
	case DIFF_SYMBOL_NO_LF_EOF:
		context = diff_get_color_opt(o, DIFF_CONTEXT);
		reset = diff_get_color_opt(o, DIFF_RESET);
		putc('\n', o->file);
		emit_line_0(o, context, NULL, 0, reset, '\\',
			    nneof, strlen(nneof));
		break;
	case DIFF_SYMBOL_SUBMODULE_HEADER:
	case DIFF_SYMBOL_SUBMODULE_ERROR:
	case DIFF_SYMBOL_SUBMODULE_PIPETHROUGH:
	case DIFF_SYMBOL_STATS_SUMMARY_INSERTS_DELETES:
	case DIFF_SYMBOL_SUMMARY:
	case DIFF_SYMBOL_STATS_LINE:
	case DIFF_SYMBOL_BINARY_DIFF_BODY:
	case DIFF_SYMBOL_CONTEXT_FRAGINFO:
		emit_line(o, "", "", line, len);
		break;
	case DIFF_SYMBOL_CONTEXT_INCOMPLETE:
	case DIFF_SYMBOL_CONTEXT_MARKER:
		context = diff_get_color_opt(o, DIFF_CONTEXT);
		reset = diff_get_color_opt(o, DIFF_RESET);
		emit_line(o, context, reset, line, len);
		break;
	case DIFF_SYMBOL_SEPARATOR:
		fprintf(o->file, "%s%c",
			diff_line_prefix(o),
			o->line_termination);
		break;
	case DIFF_SYMBOL_CONTEXT:
		set = diff_get_color_opt(o, DIFF_CONTEXT);
		reset = diff_get_color_opt(o, DIFF_RESET);
		set_sign = NULL;
		if (o->flags.dual_color_diffed_diffs) {
			char c = !len ? 0 : line[0];

			if (c == '+')
				set = diff_get_color_opt(o, DIFF_FILE_NEW);
			else if (c == '@')
				set = diff_get_color_opt(o, DIFF_FRAGINFO);
			else if (c == '-')
				set = diff_get_color_opt(o, DIFF_FILE_OLD);
		}
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_CONTEXT, line, len,
				    flags & (DIFF_SYMBOL_CONTENT_WS_MASK), 0);
		break;
	case DIFF_SYMBOL_PLUS:
		switch (flags & (DIFF_SYMBOL_MOVED_LINE |
				 DIFF_SYMBOL_MOVED_LINE_ALT |
				 DIFF_SYMBOL_MOVED_LINE_UNINTERESTING)) {
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_ALT |
		     DIFF_SYMBOL_MOVED_LINE_UNINTERESTING:
			set = diff_get_color_opt(o, DIFF_FILE_NEW_MOVED_ALT_DIM);
			break;
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_ALT:
			set = diff_get_color_opt(o, DIFF_FILE_NEW_MOVED_ALT);
			break;
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_UNINTERESTING:
			set = diff_get_color_opt(o, DIFF_FILE_NEW_MOVED_DIM);
			break;
		case DIFF_SYMBOL_MOVED_LINE:
			set = diff_get_color_opt(o, DIFF_FILE_NEW_MOVED);
			break;
		default:
			set = diff_get_color_opt(o, DIFF_FILE_NEW);
		}
		reset = diff_get_color_opt(o, DIFF_RESET);
		if (!o->flags.dual_color_diffed_diffs)
			set_sign = NULL;
		else {
			char c = !len ? 0 : line[0];

			set_sign = set;
			if (c == '-')
				set = diff_get_color_opt(o, DIFF_FILE_OLD_BOLD);
			else if (c == '@')
				set = diff_get_color_opt(o, DIFF_FRAGINFO);
			else if (c == '+')
				set = diff_get_color_opt(o, DIFF_FILE_NEW_BOLD);
			else
				set = diff_get_color_opt(o, DIFF_CONTEXT_BOLD);
			flags &= ~DIFF_SYMBOL_CONTENT_WS_MASK;
		}
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_NEW, line, len,
				    flags & DIFF_SYMBOL_CONTENT_WS_MASK,
				    flags & DIFF_SYMBOL_CONTENT_BLANK_LINE_EOF);
		break;
	case DIFF_SYMBOL_MINUS:
		switch (flags & (DIFF_SYMBOL_MOVED_LINE |
				 DIFF_SYMBOL_MOVED_LINE_ALT |
				 DIFF_SYMBOL_MOVED_LINE_UNINTERESTING)) {
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_ALT |
		     DIFF_SYMBOL_MOVED_LINE_UNINTERESTING:
			set = diff_get_color_opt(o, DIFF_FILE_OLD_MOVED_ALT_DIM);
			break;
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_ALT:
			set = diff_get_color_opt(o, DIFF_FILE_OLD_MOVED_ALT);
			break;
		case DIFF_SYMBOL_MOVED_LINE |
		     DIFF_SYMBOL_MOVED_LINE_UNINTERESTING:
			set = diff_get_color_opt(o, DIFF_FILE_OLD_MOVED_DIM);
			break;
		case DIFF_SYMBOL_MOVED_LINE:
			set = diff_get_color_opt(o, DIFF_FILE_OLD_MOVED);
			break;
		default:
			set = diff_get_color_opt(o, DIFF_FILE_OLD);
		}
		reset = diff_get_color_opt(o, DIFF_RESET);
		if (!o->flags.dual_color_diffed_diffs)
			set_sign = NULL;
		else {
			char c = !len ? 0 : line[0];

			set_sign = set;
			if (c == '+')
				set = diff_get_color_opt(o, DIFF_FILE_NEW_DIM);
			else if (c == '@')
				set = diff_get_color_opt(o, DIFF_FRAGINFO);
			else if (c == '-')
				set = diff_get_color_opt(o, DIFF_FILE_OLD_DIM);
			else
				set = diff_get_color_opt(o, DIFF_CONTEXT_DIM);
		}
		emit_line_ws_markup(o, set_sign, set, reset,
				    OUTPUT_INDICATOR_OLD, line, len,
				    flags & DIFF_SYMBOL_CONTENT_WS_MASK, 0);
		break;
	case DIFF_SYMBOL_WORDS_PORCELAIN:
		context = diff_get_color_opt(o, DIFF_CONTEXT);
		reset = diff_get_color_opt(o, DIFF_RESET);
		emit_line(o, context, reset, line, len);
		fputs("~\n", o->file);
		break;
	case DIFF_SYMBOL_WORDS:
		context = diff_get_color_opt(o, DIFF_CONTEXT);
		reset = diff_get_color_opt(o, DIFF_RESET);
		/*
		 * Skip the prefix character, if any.  With
		 * diff_suppress_blank_empty, there may be
		 * none.
		 */
		if (line[0] != '\n') {
			line++;
			len--;
		}
		emit_line(o, context, reset, line, len);
		break;
	case DIFF_SYMBOL_FILEPAIR_PLUS:
		meta = diff_get_color_opt(o, DIFF_METAINFO);
		reset = diff_get_color_opt(o, DIFF_RESET);
		fprintf(o->file, "%s%s+++ %s%s%s\n", diff_line_prefix(o), meta,
			line, reset,
			strchr(line, ' ') ? "\t" : "");
		break;
	case DIFF_SYMBOL_FILEPAIR_MINUS:
		meta = diff_get_color_opt(o, DIFF_METAINFO);
		reset = diff_get_color_opt(o, DIFF_RESET);
		fprintf(o->file, "%s%s--- %s%s%s\n", diff_line_prefix(o), meta,
			line, reset,
			strchr(line, ' ') ? "\t" : "");
		break;
	case DIFF_SYMBOL_BINARY_FILES:
	case DIFF_SYMBOL_HEADER:
		fprintf(o->file, "%s", line);
		break;
	case DIFF_SYMBOL_BINARY_DIFF_HEADER:
		fprintf(o->file, "%sGIT binary patch\n", diff_line_prefix(o));
		break;
	case DIFF_SYMBOL_BINARY_DIFF_HEADER_DELTA:
		fprintf(o->file, "%sdelta %s\n", diff_line_prefix(o), line);
		break;
	case DIFF_SYMBOL_BINARY_DIFF_HEADER_LITERAL:
		fprintf(o->file, "%sliteral %s\n", diff_line_prefix(o), line);
		break;
	case DIFF_SYMBOL_BINARY_DIFF_FOOTER:
		fputs(diff_line_prefix(o), o->file);
		fputc('\n', o->file);
		break;
	case DIFF_SYMBOL_REWRITE_DIFF:
		fraginfo = diff_get_color(o->use_color, DIFF_FRAGINFO);
		reset = diff_get_color_opt(o, DIFF_RESET);
		emit_line(o, fraginfo, reset, line, len);
		break;
	case DIFF_SYMBOL_SUBMODULE_ADD:
		set = diff_get_color_opt(o, DIFF_FILE_NEW);
		reset = diff_get_color_opt(o, DIFF_RESET);
		emit_line(o, set, reset, line, len);
		break;
	case DIFF_SYMBOL_SUBMODULE_DEL:
		set = diff_get_color_opt(o, DIFF_FILE_OLD);
		reset = diff_get_color_opt(o, DIFF_RESET);
		emit_line(o, set, reset, line, len);
		break;
	case DIFF_SYMBOL_SUBMODULE_UNTRACKED:
		fprintf(o->file, "%sSubmodule %s contains untracked content\n",
			diff_line_prefix(o), line);
		break;
	case DIFF_SYMBOL_SUBMODULE_MODIFIED:
		fprintf(o->file, "%sSubmodule %s contains modified content\n",
			diff_line_prefix(o), line);
		break;
	case DIFF_SYMBOL_STATS_SUMMARY_NO_FILES:
		emit_line(o, "", "", " 0 files changed\n",
			  strlen(" 0 files changed\n"));
		break;
	case DIFF_SYMBOL_STATS_SUMMARY_ABBREV:
		emit_line(o, "", "", " ...\n", strlen(" ...\n"));
		break;
	case DIFF_SYMBOL_WORD_DIFF:
		fprintf(o->file, "%.*s", len, line);
		break;
	case DIFF_SYMBOL_STAT_SEP:
		fputs(o->stat_sep, o->file);
		break;
	default:
		BUG("unknown diff symbol");
	}
	strbuf_release(&sb);
}

static void emit_diff_symbol(struct diff_options *o, enum diff_symbol s,
			     const char *line, int len, unsigned flags)
{
	struct emitted_diff_symbol e = {line, len, flags, 0, 0, s};

	if (o->emitted_symbols)
		append_emitted_diff_symbol(o, &e);
	else
		emit_diff_symbol_from_struct(o, &e);
}

void diff_emit_submodule_del(struct diff_options *o, const char *line)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_DEL, line, strlen(line), 0);
}

void diff_emit_submodule_add(struct diff_options *o, const char *line)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_ADD, line, strlen(line), 0);
}

void diff_emit_submodule_untracked(struct diff_options *o, const char *path)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_UNTRACKED,
			 path, strlen(path), 0);
}

void diff_emit_submodule_modified(struct diff_options *o, const char *path)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_MODIFIED,
			 path, strlen(path), 0);
}

void diff_emit_submodule_header(struct diff_options *o, const char *header)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_HEADER,
			 header, strlen(header), 0);
}

void diff_emit_submodule_error(struct diff_options *o, const char *err)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_ERROR, err, strlen(err), 0);
}

void diff_emit_submodule_pipethrough(struct diff_options *o,
				     const char *line, int len)
{
	emit_diff_symbol(o, DIFF_SYMBOL_SUBMODULE_PIPETHROUGH, line, len, 0);
}

static int new_blank_line_at_eof(struct emit_callback *ecbdata, const char *line, int len)
{
	if (!((ecbdata->ws_rule & WS_BLANK_AT_EOF) &&
	      ecbdata->blank_at_eof_in_preimage &&
	      ecbdata->blank_at_eof_in_postimage &&
	      ecbdata->blank_at_eof_in_preimage <= ecbdata->lno_in_preimage &&
	      ecbdata->blank_at_eof_in_postimage <= ecbdata->lno_in_postimage))
		return 0;
	return ws_blank_line(line, len, ecbdata->ws_rule);
}

static void emit_add_line(struct emit_callback *ecbdata,
	unsigned flags = WSEH_NEW | ecbdata->ws_rule;
	if (new_blank_line_at_eof(ecbdata, line, len))
		flags |= DIFF_SYMBOL_CONTENT_BLANK_LINE_EOF;

	emit_diff_symbol(ecbdata->opt, DIFF_SYMBOL_PLUS, line, len, flags);
static void emit_del_line(struct emit_callback *ecbdata,
	unsigned flags = WSEH_OLD | ecbdata->ws_rule;
	emit_diff_symbol(ecbdata->opt, DIFF_SYMBOL_MINUS, line, len, flags);
static void emit_context_line(struct emit_callback *ecbdata,
	unsigned flags = WSEH_CONTEXT | ecbdata->ws_rule;
	emit_diff_symbol(ecbdata->opt, DIFF_SYMBOL_CONTEXT, line, len, flags);
	const char *reverse = ecbdata->color_diff ? GIT_COLOR_REVERSE : "";
		emit_diff_symbol(ecbdata->opt,
				 DIFF_SYMBOL_CONTEXT_MARKER, line, len, 0);
	if (ecbdata->opt->flags.dual_color_diffed_diffs)
		strbuf_addstr(&msgbuf, reverse);
	if (ecbdata->opt->flags.suppress_hunk_header_line_count)
		strbuf_add(&msgbuf, atat, sizeof(atat));
	else
		strbuf_add(&msgbuf, line, ep - line);
	strbuf_complete_line(&msgbuf);
	emit_diff_symbol(ecbdata->opt,
			 DIFF_SYMBOL_CONTEXT_FRAGINFO, msgbuf.buf, msgbuf.len, 0);
static struct diff_tempfile *claim_diff_tempfile(void)
{
	BUG("diff is failing to clean up its tempfiles");
		if (is_tempfile_active(diff_temp[i].tempfile))
static void add_line_count(struct strbuf *out, int count)
		strbuf_addstr(out, "0,0");
		strbuf_addstr(out, "1");
		strbuf_addf(out, "1,%d", count);
			emit_del_line(ecb, data, len);
			emit_add_line(ecb, data, len);
	if (!endp)
		emit_diff_symbol(ecb->opt, DIFF_SYMBOL_NO_LF_EOF, NULL, 0, 0);
	struct strbuf out = STRBUF_INIT;
	if (diff_mnemonic_prefix && o->flags.reverse_diff) {
	size_one = fill_textconv(o->repo, textconv_one, one, &data_one);
	size_two = fill_textconv(o->repo, textconv_two, two, &data_two);
	ecbdata.ws_rule = whitespace_rule(o->repo->index, name_b);

	emit_diff_symbol(o, DIFF_SYMBOL_FILEPAIR_MINUS,
			 a_name.buf, a_name.len, 0);
	emit_diff_symbol(o, DIFF_SYMBOL_FILEPAIR_PLUS,
			 b_name.buf, b_name.len, 0);

	strbuf_addstr(&out, "@@ -");
		add_line_count(&out, lc_a);
		strbuf_addstr(&out, "?,?");
	strbuf_addstr(&out, " +");
	add_line_count(&out, lc_b);
	strbuf_addstr(&out, " @@\n");
	emit_diff_symbol(o, DIFF_SYMBOL_REWRITE_DIFF, out.buf, out.len, 0);
	strbuf_release(&out);

	struct diff_words_style_elem new_word, old_word, ctx;
static int fn_out_diff_words_write_helper(struct diff_options *o,
					  size_t count, const char *buf)
	struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, diff_line_prefix(o));

			const char *reset = st_el->color && *st_el->color ?
					    GIT_COLOR_RESET : NULL;
			if (st_el->color && *st_el->color)
				strbuf_addstr(&sb, st_el->color);
			strbuf_addstr(&sb, st_el->prefix);
			strbuf_add(&sb, buf, p ? p - buf : count);
			strbuf_addstr(&sb, st_el->suffix);
			if (reset)
				strbuf_addstr(&sb, reset);
			goto out;

		strbuf_addstr(&sb, newline);
		if (count) {
			emit_diff_symbol(o, DIFF_SYMBOL_WORD_DIFF,
					 sb.buf, sb.len, 0);
			strbuf_reset(&sb);
		}

out:
	if (sb.len)
		emit_diff_symbol(o, DIFF_SYMBOL_WORD_DIFF,
				 sb.buf, sb.len, 0);
	strbuf_release(&sb);
static void fn_out_diff_words_aux(void *priv,
				  long minus_first, long minus_len,
				  long plus_first, long plus_len,
				  const char *func, long funclen)
		fn_out_diff_words_write_helper(diff_words->opt,
				diff_words->current_plus);
		fn_out_diff_words_write_helper(diff_words->opt,
				&style->old_word, style->newline,
				minus_end - minus_begin, minus_begin);
		fn_out_diff_words_write_helper(diff_words->opt,
				&style->new_word, style->newline,
				plus_end - plus_begin, plus_begin);
		emit_diff_symbol(diff_words->opt, DIFF_SYMBOL_WORD_DIFF,
				 line_prefix, strlen(line_prefix), 0);
		fn_out_diff_words_write_helper(diff_words->opt,
			&style->old_word, style->newline,
			diff_words->minus.text.ptr);
	if (xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, NULL,
			  diff_words, &xpp, &xecfg))
			emit_diff_symbol(diff_words->opt, DIFF_SYMBOL_WORD_DIFF,
					 line_prefix, strlen(line_prefix), 0);
		fn_out_diff_words_write_helper(diff_words->opt,
			- diff_words->current_plus, diff_words->current_plus);
	struct diff_options *wo = ecbdata->diff_words->opt;


	if (wo->emitted_symbols) {
		struct diff_options *o = ecbdata->opt;
		struct emitted_diff_symbols *wol = wo->emitted_symbols;
		int i;

		/*
		 * NEEDSWORK:
		 * Instead of appending each, concat all words to a line?
		 */
		for (i = 0; i < wol->nr; i++)
			append_emitted_diff_symbol(o, &wol->buf[i]);

		for (i = 0; i < wol->nr; i++)
			free((void *)wol->buf[i].line);

		wol->nr = 0;
	}
static void diff_filespec_load_driver(struct diff_filespec *one,
				      struct index_state *istate)
		one->driver = userdiff_find_by_path(istate, one->path);
static const char *userdiff_word_regex(struct diff_filespec *one,
				       struct index_state *istate)
	diff_filespec_load_driver(one, istate);

	if (orig_opts->emitted_symbols)
		o->emitted_symbols =
			xcalloc(1, sizeof(struct emitted_diff_symbols));

		o->word_regex = userdiff_word_regex(one, o->repo->index);
		o->word_regex = userdiff_word_regex(two, o->repo->index);
			die("invalid regular expression: %s",
			    o->word_regex);
		st->old_word.color = diff_get_color_opt(o, DIFF_FILE_OLD);
		st->new_word.color = diff_get_color_opt(o, DIFF_FILE_NEW);
		free (ecbdata->diff_words->opt->emitted_symbols);
static unsigned long sane_truncate_line(char *line, unsigned long len)
		emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
				 ecbdata->header->buf, ecbdata->header->len, 0);
		emit_diff_symbol(o, DIFF_SYMBOL_FILEPAIR_MINUS,
				 ecbdata->label_path[0],
				 strlen(ecbdata->label_path[0]), 0);
		emit_diff_symbol(o, DIFF_SYMBOL_FILEPAIR_PLUS,
				 ecbdata->label_path[1],
				 strlen(ecbdata->label_path[1]), 0);
		len = sane_truncate_line(line, len);
		enum diff_symbol s =
			ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN ?
			DIFF_SYMBOL_WORDS_PORCELAIN : DIFF_SYMBOL_WORDS;
		emit_diff_symbol(o, s, line, len, 0);
		emit_add_line(ecbdata, line + 1, len - 1);
		emit_del_line(ecbdata, line + 1, len - 1);
		emit_context_line(ecbdata, line + 1, len - 1);
		emit_diff_symbol(o, DIFF_SYMBOL_CONTEXT_INCOMPLETE,
				 line, len, 0);
static void pprint_rename(struct strbuf *name, const char *a, const char *b)
	const char *old_name = a;
	const char *new_name = b;
		quote_c_style(a, name, NULL, 0);
		strbuf_addstr(name, " => ");
		quote_c_style(b, name, NULL, 0);
		return;
	while (*old_name && *new_name && *old_name == *new_name) {
		if (*old_name == '/')
			pfx_length = old_name - a + 1;
		old_name++;
		new_name++;
	old_name = a + len_a;
	new_name = b + len_b;
	while (a + pfx_length - pfx_adjust_for_slash <= old_name &&
	       b + pfx_length - pfx_adjust_for_slash <= new_name &&
	       *old_name == *new_name) {
		if (*old_name == '/')
			sfx_length = len_a - (old_name - a);
		old_name--;
		new_name--;
	strbuf_grow(name, pfx_length + a_midlen + b_midlen + sfx_length + 7);
		strbuf_add(name, a, pfx_length);
		strbuf_addch(name, '{');
	strbuf_add(name, a + pfx_length, a_midlen);
	strbuf_addstr(name, " => ");
	strbuf_add(name, b + pfx_length, b_midlen);
		strbuf_addch(name, '}');
		strbuf_add(name, a + len_a - sfx_length, sfx_length);
	}
}
	 * scale linearly as if the allotted width is one column shorter
static void show_graph(struct strbuf *out, char ch, int cnt,
		       const char *set, const char *reset)
	strbuf_addstr(out, set);
	strbuf_addchars(out, ch, cnt);
	strbuf_addstr(out, reset);
	struct strbuf pname = STRBUF_INIT;
	if (file->is_renamed)
		pprint_rename(&pname, file->from_name, file->name);
	else
		quote_c_style(file->name, &pname, NULL, 0);

	if (file->comments)
		strbuf_addf(&pname, " (%s)", file->comments);

	file->print_name = strbuf_detach(&pname, NULL);
static void print_stat_summary_inserts_deletes(struct diff_options *options,
		int files, int insertions, int deletions)
		emit_diff_symbol(options, DIFF_SYMBOL_STATS_SUMMARY_NO_FILES,
				 NULL, 0, 0);
		return;
	emit_diff_symbol(options, DIFF_SYMBOL_STATS_SUMMARY_INSERTS_DELETES,
			 sb.buf, sb.len, 0);
}

void print_stat_summary(FILE *fp, int files,
			int insertions, int deletions)
{
	struct diff_options o;
	memset(&o, 0, sizeof(o));
	o.file = fp;

	print_stat_summary_inserts_deletes(&o, files, insertions, deletions);
	const char *line_prefix = diff_line_prefix(options);
	struct strbuf out = STRBUF_INIT;
			strbuf_addf(&out, " %s%-*s |", prefix, len, name);
			strbuf_addf(&out, " %*s", number_width, "Bin");
				strbuf_addch(&out, '\n');
				emit_diff_symbol(options, DIFF_SYMBOL_STATS_LINE,
						 out.buf, out.len, 0);
				strbuf_reset(&out);
			strbuf_addf(&out, " %s%"PRIuMAX"%s",
			strbuf_addstr(&out, " -> ");
			strbuf_addf(&out, "%s%"PRIuMAX"%s",
			strbuf_addstr(&out, " bytes\n");
			emit_diff_symbol(options, DIFF_SYMBOL_STATS_LINE,
					 out.buf, out.len, 0);
			strbuf_reset(&out);
			strbuf_addf(&out, " %s%-*s |", prefix, len, name);
			strbuf_addstr(&out, " Unmerged\n");
			emit_diff_symbol(options, DIFF_SYMBOL_STATS_LINE,
					 out.buf, out.len, 0);
			strbuf_reset(&out);
		strbuf_addf(&out, " %s%-*s |", prefix, len, name);
		strbuf_addf(&out, " %*"PRIuMAX"%s",
		show_graph(&out, '+', add, add_c, reset);
		show_graph(&out, '-', del, del_c, reset);
		strbuf_addch(&out, '\n');
		emit_diff_symbol(options, DIFF_SYMBOL_STATS_LINE,
				 out.buf, out.len, 0);
		strbuf_reset(&out);
			emit_diff_symbol(options,
					 DIFF_SYMBOL_STATS_SUMMARY_ABBREV,
					 NULL, 0, 0);

	print_stat_summary_inserts_deletes(options, total_files, adds, dels);
	strbuf_release(&out);
		int deleted = data->files[i]->deleted;
	print_stat_summary_inserts_deletes(options, total_files, adds, dels);
	unsigned long sum_changes = 0;
		unsigned long changes;
			changes = gather_dirstat(opt, dir, changed, f->name, newbaselen);
			changes = f->changed;
		sum_changes += changes;
		if (sum_changes) {
			int permille = sum_changes * 1000 / changed;
	return sum_changes;
	dir.cumulative = options->flags.dirstat_cumulative;
		if (p->one->oid_valid && p->two->oid_valid &&
		    oideq(&p->one->oid, &p->two->oid)) {
		if (options->flags.dirstat_by_file) {
			diff_populate_filespec(options->repo, p->one, 0);
			diff_populate_filespec(options->repo, p->two, 0);
			diffcore_count_changes(options->repo,
					       p->one, p->two, NULL, NULL,
			diff_populate_filespec(options->repo, p->one, CHECK_SIZE_ONLY);
			diff_populate_filespec(options->repo, p->two, CHECK_SIZE_ONLY);
		 * be identical, but since the oid changed, we
	dir.cumulative = options->flags.dirstat_cumulative;
void free_diffstat_info(struct diffstat_t *diffstat)
		free(f->print_name);
	/* line[1] through line[marker_size-1] are same as firstchar */
static void checkdiff_consume_hunk(void *priv,
				   long ob, long on, long nb, long nn,
				   const char *func, long funclen)

{
	struct checkdiff_t *data = priv;
	data->lineno = nb - 1;
}

static void emit_binary_diff_body(struct diff_options *o,
				  mmfile_t *one, mmfile_t *two)
		char *s = xstrfmt("%"PRIuMAX , (uintmax_t)orig_size);
		emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_HEADER_DELTA,
				 s, strlen(s), 0);
		free(s);
	} else {
		char *s = xstrfmt("%lu", two->size);
		emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_HEADER_LITERAL,
				 s, strlen(s), 0);
		free(s);
		int len;
		char line[71];

		len = strlen(line);
		line[len++] = '\n';
		line[len] = '\0';

		emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_BODY,
				 line, len, 0);
	emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_FOOTER, NULL, 0, 0);
static void emit_binary_diff(struct diff_options *o,
			     mmfile_t *one, mmfile_t *two)
	emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_HEADER, NULL, 0, 0);
	emit_binary_diff_body(o, one, two);
	emit_binary_diff_body(o, two, one);
int diff_filespec_is_binary(struct repository *r,
			    struct diff_filespec *one)
		diff_filespec_load_driver(one, r->index);
				diff_populate_filespec(r, one, CHECK_BINARY);
static const struct userdiff_funcname *
diff_funcname_pattern(struct diff_options *o, struct diff_filespec *one)
	diff_filespec_load_driver(one, o->repo->index);
struct userdiff_driver *get_textconv(struct repository *r,
				     struct diff_filespec *one)
	diff_filespec_load_driver(one, r->index);
	return userdiff_get_textconv(r, one->driver);
	if (o->flags.reverse_diff) {
		show_submodule_summary(o, one->path ? one->path : two->path,
				two->dirty_submodule);
		show_submodule_inline_diff(o, one->path ? one->path : two->path,
				two->dirty_submodule);
	if (o->flags.allow_textconv) {
		textconv_one = get_textconv(o->repo, one);
		textconv_two = get_textconv(o->repo, two);
		    (textconv_one || !diff_filespec_is_binary(o->repo, one)) &&
		    (textconv_two || !diff_filespec_is_binary(o->repo, two))) {
			emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
					 header.buf, header.len, 0);
					  textconv_one, textconv_two, o);
		emit_diff_symbol(o, DIFF_SYMBOL_HEADER, header.buf,
				 header.len, 0);
	} else if (!o->flags.text &&
		   ( (!textconv_one && diff_filespec_is_binary(o->repo, one)) ||
		     (!textconv_two && diff_filespec_is_binary(o->repo, two)) )) {
		struct strbuf sb = STRBUF_INIT;
		    !o->flags.binary) {
			if (oideq(&one->oid, &two->oid)) {
					emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
							 header.buf, header.len,
							 0);
			emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
					 header.buf, header.len, 0);
			strbuf_addf(&sb, "%sBinary files %s and %s differ\n",
				    diff_line_prefix(o), lbl[0], lbl[1]);
			emit_diff_symbol(o, DIFF_SYMBOL_BINARY_FILES,
					 sb.buf, sb.len, 0);
			strbuf_release(&sb);
		if (fill_mmfile(o->repo, &mf1, one) < 0 ||
		    fill_mmfile(o->repo, &mf2, two) < 0)
				emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
						 header.buf, header.len, 0);
		emit_diff_symbol(o, DIFF_SYMBOL_HEADER, header.buf, header.len, 0);
		if (o->flags.binary)
			emit_binary_diff(o, &mf1, &mf2);
		else {
			strbuf_addf(&sb, "%sBinary files %s and %s differ\n",
				    diff_line_prefix(o), lbl[0], lbl[1]);
			emit_diff_symbol(o, DIFF_SYMBOL_BINARY_FILES,
					 sb.buf, sb.len, 0);
			strbuf_release(&sb);
		}
		const char *diffopts;
			emit_diff_symbol(o, DIFF_SYMBOL_HEADER,
					 header.buf, header.len, 0);
		mf1.size = fill_textconv(o->repo, textconv_one, one, &mf1.ptr);
		mf2.size = fill_textconv(o->repo, textconv_two, two, &mf2.ptr);
		pe = diff_funcname_pattern(o, one);
			pe = diff_funcname_pattern(o, two);
		if (o->flags.suppress_diff_headers)
			lbl[0] = NULL;
		ecbdata.ws_rule = whitespace_rule(o->repo->index, name_b);
		if (header.len && !o->flags.suppress_diff_headers)
			ecbdata.header = &header;
		xpp.anchors = o->anchors;
		xpp.anchors_nr = o->anchors_nr;
		if (o->flags.funccontext)

		diffopts = getenv("GIT_DIFF_OPTS");

		if (xdi_diff_outf(&mf1, &mf2, NULL, fn_out_consume,
				  &ecbdata, &xpp, &xecfg))
static char *get_compact_summary(const struct diff_filepair *p, int is_renamed)
{
	if (!is_renamed) {
		if (p->status == DIFF_STATUS_ADDED) {
			if (S_ISLNK(p->two->mode))
				return "new +l";
			else if ((p->two->mode & 0777) == 0755)
				return "new +x";
			else
				return "new";
		} else if (p->status == DIFF_STATUS_DELETED)
			return "gone";
	}
	if (S_ISLNK(p->one->mode) && !S_ISLNK(p->two->mode))
		return "mode -l";
	else if (!S_ISLNK(p->one->mode) && S_ISLNK(p->two->mode))
		return "mode +l";
	else if ((p->one->mode & 0777) == 0644 &&
		 (p->two->mode & 0777) == 0755)
		return "mode +x";
	else if ((p->one->mode & 0777) == 0755 &&
		 (p->two->mode & 0777) == 0644)
		return "mode -x";
	return NULL;
}

	if (o->flags.stat_with_summary)
		data->comments = get_compact_summary(p, data->is_renamed);
	same_contents = oideq(&one->oid, &two->oid);
	if (diff_filespec_is_binary(o->repo, one) ||
	    diff_filespec_is_binary(o->repo, two)) {
			data->added = diff_filespec_size(o->repo, two);
			data->deleted = diff_filespec_size(o->repo, one);
		diff_populate_filespec(o->repo, one, 0);
		diff_populate_filespec(o->repo, two, 0);
		if (fill_mmfile(o->repo, &mf1, one) < 0 ||
		    fill_mmfile(o->repo, &mf2, two) < 0)
		xpp.anchors = o->anchors;
		xpp.anchors_nr = o->anchors_nr;
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  diffstat_consume, diffstat, &xpp, &xecfg))
	data.ws_rule = whitespace_rule(o->repo->index, attr_path);
	data.conflict_marker_size = ll_merge_marker_size(o->repo->index, attr_path);
	if (fill_mmfile(o->repo, &mf1, one) < 0 ||
	    fill_mmfile(o->repo, &mf2, two) < 0)
	if (diff_filespec_is_binary(o->repo, two))
		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume_hunk,
				  checkdiff_consume, &data,
		o->flags.check_failed = 1;
static int reuse_worktree_file(struct index_state *istate,
			       const char *name,
			       const struct object_id *oid,
			       int want_file)
	if (!istate->cache)
	if (!FAST_WORKING_DIRECTORY && !want_file && has_object_pack(oid))
	if (!want_file && would_convert_to_git(istate, name))
	pos = index_name_pos(istate, name, len);
	ce = istate->cache[pos];
	if (!oideq(oid, &ce->oid) || !S_ISREG(ce->ce_mode))
	    (!lstat(name, &st) && !ie_match_stat(istate, ce, &st, 0)))
int diff_populate_filespec(struct repository *r,
			   struct diff_filespec *s,
			   unsigned int flags)
	int conv_flags = global_conv_flags_eol;
	if (conv_flags & CONV_EOL_RNDTRP_DIE)
		conv_flags = CONV_EOL_RNDTRP_WARN;
	    reuse_worktree_file(r->index, s->path, &s->oid, 0)) {
		err_empty:
			err = -1;
		empty:
			s->data = (char *)"";
			s->size = 0;
			return err;
		if (size_only && !would_convert_to_git(r->index, s->path))
		if (convert_to_git(r->index, s->path, s->data, s->size, &buf, conv_flags)) {
			type = oid_object_info(r, &s->oid, &s->size);
		s->data = repo_read_object_file(r, &s->oid, &type, &s->size);
static void prep_temp_blob(struct index_state *istate,
			   const char *path, struct diff_tempfile *temp,
	struct strbuf tempfile = STRBUF_INIT;
	struct checkout_metadata meta;

	init_checkout_metadata(&meta, NULL, NULL, oid);
	strbuf_addstr(&tempfile, "XXXXXX_");
	strbuf_addstr(&tempfile, base);
	temp->tempfile = mks_tempfile_ts(tempfile.buf, strlen(base) + 1);
	if (!temp->tempfile)
	if (convert_to_working_tree(istate, path,
			(const char *)blob, (size_t)size, &buf, &meta)) {
	if (write_in_full(temp->tempfile->fd, blob, size) < 0 ||
	    close_tempfile_gently(temp->tempfile))
	temp->name = get_tempfile_path(temp->tempfile);
	strbuf_release(&tempfile);
static struct diff_tempfile *prepare_temp_file(struct repository *r,
					       const char *name,
					       struct diff_filespec *one)
	     reuse_worktree_file(r->index, name, &one->oid, 1))) {
			prep_temp_blob(r->index, name, temp, sb.buf, sb.len,
		if (diff_populate_filespec(r, one, 0))
		prep_temp_blob(r->index, name, temp,
			       one->data, one->size,
static void add_external_diff_name(struct repository *r,
				   struct argv_array *argv,
	struct diff_tempfile *temp = prepare_temp_file(r, name, df);
		add_external_diff_name(o->repo, &argv, name, one);
			add_external_diff_name(o->repo, &argv, name, two);
			add_external_diff_name(o->repo, &argv, other, two);
	diff_free_filespec_data(one);
	diff_free_filespec_data(two);
		return find_unique_abbrev(oid, abbrev);
		if (abbrev > the_hash_algo->hexsz)
			BUG("oid abbreviation out of range: %d", abbrev);
	if (one && two && !oideq(&one->oid, &two->oid)) {
		const unsigned hexsz = the_hash_algo->hexsz;
		int abbrev = o->flags.full_index ? hexsz : DEFAULT_ABBREV;
		if (o->flags.binary) {
			if ((!fill_mmfile(o->repo, &mf, one) &&
			     diff_filespec_is_binary(o->repo, one)) ||
			    (!fill_mmfile(o->repo, &mf, two) &&
			     diff_filespec_is_binary(o->repo, two)))
				abbrev = hexsz;
	if (o->flags.allow_external) {
		struct userdiff_driver *drv;

		drv = userdiff_find_by_path(o->repo->index, attr_path);
		run_external_diff(pgm, name, other, one, two, xfrm_msg, o);
static void diff_fill_oid_info(struct diff_filespec *one, struct index_state *istate)
			if (index_path(istate, &one->oid, one->path, &st, 0))
	if (*namep && !is_absolute_path(*namep)) {
	if (*otherp && !is_absolute_path(*otherp)) {
	name  = one->path;
	other = (strcmp(name, two->path) ? two->path : NULL);
	if (!o->flags.allow_external)
	diff_fill_oid_info(one, o->repo->index);
	diff_fill_oid_info(two, o->repo->index);
			     one, null, &msg,
			     o, p);
		builtin_diffstat(p->one->path, NULL, NULL, NULL,
				 diffstat, o, p);
	diff_fill_oid_info(p->one, o->repo->index);
	diff_fill_oid_info(p->two, o->repo->index);
	builtin_diffstat(name, other, p->one, p->two,
			 diffstat, o, p);
	diff_fill_oid_info(p->one, o->repo->index);
	diff_fill_oid_info(p->two, o->repo->index);
static void prep_parse_options(struct diff_options *options);

void repo_diff_setup(struct repository *r, struct diff_options *options)
	options->repo = r;
	options->output_indicators[OUTPUT_INDICATOR_NEW] = '+';
	options->output_indicators[OUTPUT_INDICATOR_OLD] = '-';
	options->output_indicators[OUTPUT_INDICATOR_CONTEXT] = ' ';
	options->flags.rename_empty = 1;
	options->objfind = NULL;

	options->color_moved = diff_color_moved_default;
	options->color_moved_ws_handling = diff_color_moved_ws_default;

	prep_parse_options(options);
	unsigned check_mask = DIFF_FORMAT_NAME |
			      DIFF_FORMAT_NAME_STATUS |
			      DIFF_FORMAT_CHECKDIFF |
			      DIFF_FORMAT_NO_OUTPUT;
	/*
	 * This must be signed because we're comparing against a potentially
	 * negative value.
	 */
	const int hexsz = the_hash_algo->hexsz;
	if (HAS_MULTI_BITS(options->output_format & check_mask))
	if (HAS_MULTI_BITS(options->pickaxe_opts & DIFF_PICKAXE_KINDS_MASK))
		die(_("-G, -S and --find-object are mutually exclusive"));

	if ((options->xdl_opts & XDF_WHITESPACE_FLAGS))
		options->flags.diff_from_contents = 1;
		options->flags.diff_from_contents = 0;
	if (options->flags.find_copies_harder)
	if (!options->flags.relative_name)
		options->flags.recursive = 1;
	if (options->pickaxe_opts & DIFF_PICKAXE_KINDS_MASK)
		options->flags.recursive = 1;
		options->flags.dirty_submodules = 1;
	if (hexsz < options->abbrev)
		options->abbrev = hexsz; /* full */
	if (options->flags.quick) {
		options->flags.exit_with_status = 1;
	if (options->flags.follow_renames && options->pathspec.nr != 1)
	if (!options->use_color || external_diff())
		options->color_moved = 0;
	FREE_AND_NULL(options->parseopts);
static int diff_opt_stat(const struct option *opt, const char *value, int unset)
{
	struct diff_options *options = opt->value;
	int width = options->stat_width;
	int name_width = options->stat_name_width;
	int graph_width = options->stat_graph_width;
	int count = options->stat_count;
	char *end;

	BUG_ON_OPT_NEG(unset);

	if (!strcmp(opt->long_name, "stat")) {
		if (value) {
			width = strtoul(value, &end, 10);
			if (*end == ',')
				name_width = strtoul(end+1, &end, 10);
			if (*end == ',')
				count = strtoul(end+1, &end, 10);
			if (*end)
				return error(_("invalid --stat value: %s"), value);
		}
	} else if (!strcmp(opt->long_name, "stat-width")) {
		width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-name-width")) {
		name_width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-graph-width")) {
		graph_width = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else if (!strcmp(opt->long_name, "stat-count")) {
		count = strtoul(value, &end, 10);
		if (*end)
			return error(_("%s expects a numerical value"),
				     opt->long_name);
	} else
		BUG("%s should not get here", opt->long_name);

	options->output_format |= DIFF_FORMAT_DIFFSTAT;
	options->stat_name_width = name_width;
	options->stat_graph_width = graph_width;
	options->stat_width = width;
	options->stat_count = count;
	return 0;
}

static int parse_dirstat_opt(struct diff_options *options, const char *params)
{
	struct strbuf errmsg = STRBUF_INIT;
	if (parse_dirstat_params(options, params, &errmsg))
		die(_("Failed to parse --dirstat/-X option parameter:\n%s"),
		    errmsg.buf);
	strbuf_release(&errmsg);
	/*
	 * The caller knows a dirstat-related option is given from the command
	 * line; allow it to say "return this_function();"
	 */
	options->output_format |= DIFF_FORMAT_DIRSTAT;
	return 1;
}

static const char diff_status_letters[] = {
	DIFF_STATUS_ADDED,
	DIFF_STATUS_COPIED,
	DIFF_STATUS_DELETED,
	DIFF_STATUS_MODIFIED,
	DIFF_STATUS_RENAMED,
	DIFF_STATUS_TYPE_CHANGED,
	DIFF_STATUS_UNKNOWN,
	DIFF_STATUS_UNMERGED,
	DIFF_STATUS_FILTER_AON,
	DIFF_STATUS_FILTER_BROKEN,
	'\0',
};

static unsigned int filter_bit['Z' + 1];

static void prepare_filter_bits(void)
{
	int i;

	if (!filter_bit[DIFF_STATUS_ADDED]) {
		for (i = 0; diff_status_letters[i]; i++)
			filter_bit[(int) diff_status_letters[i]] = (1 << i);
	}
}

static unsigned filter_bit_tst(char status, const struct diff_options *opt)
{
	return opt->filter & filter_bit[(int) status];
}

unsigned diff_filter_bit(char status)
{
	prepare_filter_bits();
	return filter_bit[(int) status];
}

static int diff_opt_diff_filter(const struct option *option,
				const char *optarg, int unset)
{
	struct diff_options *opt = option->value;
	int i, optch;

	BUG_ON_OPT_NEG(unset);
	prepare_filter_bits();

	/*
	 * If there is a negation e.g. 'd' in the input, and we haven't
	 * initialized the filter field with another --diff-filter, start
	 * from full set of bits, except for AON.
	 */
	if (!opt->filter) {
		for (i = 0; (optch = optarg[i]) != '\0'; i++) {
			if (optch < 'a' || 'z' < optch)
				continue;
			opt->filter = (1 << (ARRAY_SIZE(diff_status_letters) - 1)) - 1;
			opt->filter &= ~filter_bit[DIFF_STATUS_FILTER_AON];
			break;
		}
	}

	for (i = 0; (optch = optarg[i]) != '\0'; i++) {
		unsigned int bit;
		int negate;

		if ('a' <= optch && optch <= 'z') {
			negate = 1;
			optch = toupper(optch);
		} else {
			negate = 0;
		}

		bit = (0 <= optch && optch <= 'Z') ? filter_bit[optch] : 0;
		if (!bit)
			return error(_("unknown change class '%c' in --diff-filter=%s"),
				     optarg[i], optarg);
		if (negate)
			opt->filter &= ~bit;
		else
			opt->filter |= bit;
	}
	return 0;
}

static void enable_patch_output(int *fmt)
{
	*fmt &= ~DIFF_FORMAT_NO_OUTPUT;
	*fmt |= DIFF_FORMAT_PATCH;
}

static int diff_opt_ws_error_highlight(const struct option *option,
				       const char *arg, int unset)
{
	struct diff_options *opt = option->value;
	int val = parse_ws_error_highlight(arg);

	BUG_ON_OPT_NEG(unset);
	if (val < 0)
		return error(_("unknown value after ws-error-highlight=%.*s"),
			     -1 - val, arg);
	opt->ws_error_highlight = val;
	return 0;
}

static int diff_opt_find_object(const struct option *option,
				const char *arg, int unset)
{
	struct diff_options *opt = option->value;
	struct object_id oid;

	BUG_ON_OPT_NEG(unset);
	if (get_oid(arg, &oid))
		return error(_("unable to resolve '%s'"), arg);

	if (!opt->objfind)
		opt->objfind = xcalloc(1, sizeof(*opt->objfind));

	opt->pickaxe_opts |= DIFF_PICKAXE_KIND_OBJFIND;
	opt->flags.recursive = 1;
	opt->flags.tree_in_recursive = 1;
	oidset_insert(opt->objfind, &oid);
	return 0;
}

static int diff_opt_anchored(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	ALLOC_GROW(options->anchors, options->anchors_nr + 1,
		   options->anchors_alloc);
	options->anchors[options->anchors_nr++] = xstrdup(arg);
	return 0;
}

static int diff_opt_binary(const struct option *opt,
			   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	enable_patch_output(&options->output_format);
	options->flags.binary = 1;
	return 0;
}

static int diff_opt_break_rewrites(const struct option *opt,
				   const char *arg, int unset)
{
	int *break_opt = opt->value;
	int opt1, opt2;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	opt1 = parse_rename_score(&arg);
	if (*arg == 0)
		opt2 = 0;
	else if (*arg != '/')
		return error(_("%s expects <n>/<m> form"), opt->long_name);
	else {
		arg++;
		opt2 = parse_rename_score(&arg);
	}
	if (*arg != 0)
		return error(_("%s expects <n>/<m> form"), opt->long_name);
	*break_opt = opt1 | (opt2 << 16);
	return 0;
}

static int diff_opt_char(const struct option *opt,
			 const char *arg, int unset)
{
	char *value = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (arg[1])
		return error(_("%s expects a character, got '%s'"),
			     opt->long_name, arg);
	*value = arg[0];
	return 0;
}

static int diff_opt_color_moved(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	if (unset) {
		options->color_moved = COLOR_MOVED_NO;
	} else if (!arg) {
		if (diff_color_moved_default)
			options->color_moved = diff_color_moved_default;
		if (options->color_moved == COLOR_MOVED_NO)
			options->color_moved = COLOR_MOVED_DEFAULT;
	} else {
		int cm = parse_color_moved(arg);
		if (cm < 0)
			return error(_("bad --color-moved argument: %s"), arg);
		options->color_moved = cm;
	}
	return 0;
}

static int diff_opt_color_moved_ws(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	unsigned cm;

	if (unset) {
		options->color_moved_ws_handling = 0;
		return 0;
	}

	cm = parse_color_moved_ws(arg);
	if (cm & COLOR_MOVED_WS_ERROR)
		return error(_("invalid mode '%s' in --color-moved-ws"), arg);
	options->color_moved_ws_handling = cm;
	return 0;
}

static int diff_opt_color_words(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->use_color = 1;
	options->word_diff = DIFF_WORDS_COLOR;
	options->word_regex = arg;
	return 0;
}

static int diff_opt_compact_summary(const struct option *opt,
				    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.stat_with_summary = 0;
	} else {
		options->flags.stat_with_summary = 1;
		options->output_format |= DIFF_FORMAT_DIFFSTAT;
	}
	return 0;
}

static int diff_opt_diff_algorithm(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	long value = parse_algorithm_value(arg);

	BUG_ON_OPT_NEG(unset);
	if (value < 0)
		return error(_("option diff-algorithm accepts \"myers\", "
			       "\"minimal\", \"patience\" and \"histogram\""));

	/* clear out previous settings */
	DIFF_XDL_CLR(options, NEED_MINIMAL);
	options->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
	options->xdl_opts |= value;
	return 0;
}

static int diff_opt_dirstat(const struct option *opt,
			    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!strcmp(opt->long_name, "cumulative")) {
		if (arg)
			BUG("how come --cumulative take a value?");
		arg = "cumulative";
	} else if (!strcmp(opt->long_name, "dirstat-by-file"))
		parse_dirstat_opt(options, "files");
	parse_dirstat_opt(options, arg ? arg : "");
	return 0;
}

static int diff_opt_find_copies(const struct option *opt,
				const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	options->rename_score = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("invalid argument to %s"), opt->long_name);

	if (options->detect_rename == DIFF_DETECT_COPY)
		options->flags.find_copies_harder = 1;
	else
		options->detect_rename = DIFF_DETECT_COPY;

	return 0;
}

static int diff_opt_find_renames(const struct option *opt,
				 const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	options->rename_score = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("invalid argument to %s"), opt->long_name);

	options->detect_rename = DIFF_DETECT_RENAME;
	return 0;
}

static int diff_opt_follow(const struct option *opt,
			   const char *arg, int unset)
	struct diff_options *options = opt->value;
	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.follow_renames = 0;
		options->flags.default_follow_renames = 0;
	} else {
		options->flags.follow_renames = 1;
	return 0;
static int diff_opt_ignore_submodules(const struct option *opt,
				      const char *arg, int unset)
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "all";
	options->flags.override_submodule_config = 1;
	handle_ignore_submodules_arg(options, arg);
	return 0;
static int diff_opt_line_prefix(const struct option *opt,
				const char *optarg, int unset)
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->line_prefix = optarg;
	options->line_prefix_length = strlen(options->line_prefix);
	graph_setup_line_prefix(options);
	return 0;
static int diff_opt_no_prefix(const struct option *opt,
			      const char *optarg, int unset)
{
	struct diff_options *options = opt->value;
	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(optarg);
	options->a_prefix = "";
	options->b_prefix = "";
	return 0;
}
static enum parse_opt_result diff_opt_output(struct parse_opt_ctx_t *ctx,
					     const struct option *opt,
					     const char *arg, int unset)
	struct diff_options *options = opt->value;
	char *path;
	BUG_ON_OPT_NEG(unset);
	path = prefix_filename(ctx->prefix, arg);
	options->file = xfopen(path, "w");
	options->close_file = 1;
	if (options->use_color != GIT_COLOR_ALWAYS)
		options->use_color = GIT_COLOR_NEVER;
	free(path);
	return 0;
static int diff_opt_patience(const struct option *opt,
			     const char *arg, int unset)
	struct diff_options *options = opt->value;
	int i;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	/*
	 * Both --patience and --anchored use PATIENCE_DIFF
	 * internally, so remove any anchors previously
	 * specified.
	 */
	for (i = 0; i < options->anchors_nr; i++)
		free(options->anchors[i]);
	options->anchors_nr = 0;
	return 0;
static int diff_opt_pickaxe_regex(const struct option *opt,
				  const char *arg, int unset)
	struct diff_options *options = opt->value;
	BUG_ON_OPT_NEG(unset);
	options->pickaxe = arg;
	options->pickaxe_opts |= DIFF_PICKAXE_KIND_G;
	return 0;
}
static int diff_opt_pickaxe_string(const struct option *opt,
				   const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	BUG_ON_OPT_NEG(unset);
	options->pickaxe = arg;
	options->pickaxe_opts |= DIFF_PICKAXE_KIND_S;
	return 0;
}
static int diff_opt_relative(const struct option *opt,
			     const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	BUG_ON_OPT_NEG(unset);
	options->flags.relative_name = 1;
	if (arg)
		options->prefix = arg;
static int diff_opt_submodule(const struct option *opt,
			      const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "log";
	if (parse_submodule_params(options, arg))
		return error(_("failed to parse --submodule option parameter: '%s'"),
			     arg);
	return 0;
static int diff_opt_textconv(const struct option *opt,
			     const char *arg, int unset)
	struct diff_options *options = opt->value;
	BUG_ON_OPT_ARG(arg);
	if (unset) {
		options->flags.allow_textconv = 0;
	} else {
		options->flags.allow_textconv = 1;
		options->flags.textconv_set_via_cmdline = 1;
	return 0;
static int diff_opt_unified(const struct option *opt,
			    const char *arg, int unset)
	struct diff_options *options = opt->value;
	char *s;
	BUG_ON_OPT_NEG(unset);
	if (arg) {
		options->context = strtol(arg, &s, 10);
		if (*s)
			return error(_("%s expects a numerical value"), "--unified");
	enable_patch_output(&options->output_format);
	return 0;
}

static int diff_opt_word_diff(const struct option *opt,
			      const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (arg) {
			return error(_("bad --word-diff argument: %s"), arg);
	} else {
	}
	return 0;
}

static int diff_opt_word_diff_regex(const struct option *opt,
				    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (options->word_diff == DIFF_WORDS_NONE)
		options->word_diff = DIFF_WORDS_PLAIN;
	options->word_regex = arg;
	return 0;
}

static void prep_parse_options(struct diff_options *options)
{
	struct option parseopts[] = {
		OPT_GROUP(N_("Diff output format options")),
		OPT_BITOP('p', "patch", &options->output_format,
			  N_("generate patch"),
			  DIFF_FORMAT_PATCH, DIFF_FORMAT_NO_OUTPUT),
		OPT_BIT_F('s', "no-patch", &options->output_format,
			  N_("suppress diff output"),
			  DIFF_FORMAT_NO_OUTPUT, PARSE_OPT_NONEG),
		OPT_BITOP('u', NULL, &options->output_format,
			  N_("generate patch"),
			  DIFF_FORMAT_PATCH, DIFF_FORMAT_NO_OUTPUT),
		OPT_CALLBACK_F('U', "unified", options, N_("<n>"),
			       N_("generate diffs with <n> lines context"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_unified),
		OPT_BOOL('W', "function-context", &options->flags.funccontext,
			 N_("generate diffs with <n> lines context")),
		OPT_BIT_F(0, "raw", &options->output_format,
			  N_("generate the diff in raw format"),
			  DIFF_FORMAT_RAW, PARSE_OPT_NONEG),
		OPT_BITOP(0, "patch-with-raw", &options->output_format,
			  N_("synonym for '-p --raw'"),
			  DIFF_FORMAT_PATCH | DIFF_FORMAT_RAW,
			  DIFF_FORMAT_NO_OUTPUT),
		OPT_BITOP(0, "patch-with-stat", &options->output_format,
			  N_("synonym for '-p --stat'"),
			  DIFF_FORMAT_PATCH | DIFF_FORMAT_DIFFSTAT,
			  DIFF_FORMAT_NO_OUTPUT),
		OPT_BIT_F(0, "numstat", &options->output_format,
			  N_("machine friendly --stat"),
			  DIFF_FORMAT_NUMSTAT, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "shortstat", &options->output_format,
			  N_("output only the last line of --stat"),
			  DIFF_FORMAT_SHORTSTAT, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('X', "dirstat", options, N_("<param1,param2>..."),
			       N_("output the distribution of relative amount of changes for each sub-directory"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_dirstat),
		OPT_CALLBACK_F(0, "cumulative", options, NULL,
			       N_("synonym for --dirstat=cumulative"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_dirstat),
		OPT_CALLBACK_F(0, "dirstat-by-file", options, N_("<param1,param2>..."),
			       N_("synonym for --dirstat=files,param1,param2..."),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_dirstat),
		OPT_BIT_F(0, "check", &options->output_format,
			  N_("warn if changes introduce conflict markers or whitespace errors"),
			  DIFF_FORMAT_CHECKDIFF, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "summary", &options->output_format,
			  N_("condensed summary such as creations, renames and mode changes"),
			  DIFF_FORMAT_SUMMARY, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "name-only", &options->output_format,
			  N_("show only names of changed files"),
			  DIFF_FORMAT_NAME, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "name-status", &options->output_format,
			  N_("show only names and status of changed files"),
			  DIFF_FORMAT_NAME_STATUS, PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "stat", options, N_("<width>[,<name-width>[,<count>]]"),
			       N_("generate diffstat"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-width", options, N_("<width>"),
			       N_("generate diffstat with a given width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-name-width", options, N_("<width>"),
			       N_("generate diffstat with a given name width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-graph-width", options, N_("<width>"),
			       N_("generate diffstat with a given graph width"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "stat-count", options, N_("<count>"),
			       N_("generate diffstat with limited lines"),
			       PARSE_OPT_NONEG, diff_opt_stat),
		OPT_CALLBACK_F(0, "compact-summary", options, NULL,
			       N_("generate compact summary in diffstat"),
			       PARSE_OPT_NOARG, diff_opt_compact_summary),
		OPT_CALLBACK_F(0, "binary", options, NULL,
			       N_("output a binary diff that can be applied"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG, diff_opt_binary),
		OPT_BOOL(0, "full-index", &options->flags.full_index,
			 N_("show full pre- and post-image object names on the \"index\" lines")),
		OPT_COLOR_FLAG(0, "color", &options->use_color,
			       N_("show colored diff")),
		OPT_CALLBACK_F(0, "ws-error-highlight", options, N_("<kind>"),
			       N_("highlight whitespace errors in the 'context', 'old' or 'new' lines in the diff"),
			       PARSE_OPT_NONEG, diff_opt_ws_error_highlight),
		OPT_SET_INT('z', NULL, &options->line_termination,
			    N_("do not munge pathnames and use NULs as output field terminators in --raw or --numstat"),
			    0),
		OPT__ABBREV(&options->abbrev),
		OPT_STRING_F(0, "src-prefix", &options->a_prefix, N_("<prefix>"),
			     N_("show the given source prefix instead of \"a/\""),
			     PARSE_OPT_NONEG),
		OPT_STRING_F(0, "dst-prefix", &options->b_prefix, N_("<prefix>"),
			     N_("show the given destination prefix instead of \"b/\""),
			     PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "line-prefix", options, N_("<prefix>"),
			       N_("prepend an additional prefix to every line of output"),
			       PARSE_OPT_NONEG, diff_opt_line_prefix),
		OPT_CALLBACK_F(0, "no-prefix", options, NULL,
			       N_("do not show any source or destination prefix"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG, diff_opt_no_prefix),
		OPT_INTEGER_F(0, "inter-hunk-context", &options->interhunkcontext,
			      N_("show context between diff hunks up to the specified number of lines"),
			      PARSE_OPT_NONEG),
		OPT_CALLBACK_F(0, "output-indicator-new",
			       &options->output_indicators[OUTPUT_INDICATOR_NEW],
			       N_("<char>"),
			       N_("specify the character to indicate a new line instead of '+'"),
			       PARSE_OPT_NONEG, diff_opt_char),
		OPT_CALLBACK_F(0, "output-indicator-old",
			       &options->output_indicators[OUTPUT_INDICATOR_OLD],
			       N_("<char>"),
			       N_("specify the character to indicate an old line instead of '-'"),
			       PARSE_OPT_NONEG, diff_opt_char),
		OPT_CALLBACK_F(0, "output-indicator-context",
			       &options->output_indicators[OUTPUT_INDICATOR_CONTEXT],
			       N_("<char>"),
			       N_("specify the character to indicate a context instead of ' '"),
			       PARSE_OPT_NONEG, diff_opt_char),

		OPT_GROUP(N_("Diff rename options")),
		OPT_CALLBACK_F('B', "break-rewrites", &options->break_opt, N_("<n>[/<m>]"),
			       N_("break complete rewrite changes into pairs of delete and create"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_break_rewrites),
		OPT_CALLBACK_F('M', "find-renames", options, N_("<n>"),
			       N_("detect renames"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_find_renames),
		OPT_SET_INT_F('D', "irreversible-delete", &options->irreversible_delete,
			      N_("omit the preimage for deletes"),
			      1, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('C', "find-copies", options, N_("<n>"),
			       N_("detect copies"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_find_copies),
		OPT_BOOL(0, "find-copies-harder", &options->flags.find_copies_harder,
			 N_("use unmodified files as source to find copies")),
		OPT_SET_INT_F(0, "no-renames", &options->detect_rename,
			      N_("disable rename detection"),
			      0, PARSE_OPT_NONEG),
		OPT_BOOL(0, "rename-empty", &options->flags.rename_empty,
			 N_("use empty blobs as rename source")),
		OPT_CALLBACK_F(0, "follow", options, NULL,
			       N_("continue listing the history of a file beyond renames"),
			       PARSE_OPT_NOARG, diff_opt_follow),
		OPT_INTEGER('l', NULL, &options->rename_limit,
			    N_("prevent rename/copy detection if the number of rename/copy targets exceeds given limit")),

		OPT_GROUP(N_("Diff algorithm options")),
		OPT_BIT(0, "minimal", &options->xdl_opts,
			N_("produce the smallest possible diff"),
			XDF_NEED_MINIMAL),
		OPT_BIT_F('w', "ignore-all-space", &options->xdl_opts,
			  N_("ignore whitespace when comparing lines"),
			  XDF_IGNORE_WHITESPACE, PARSE_OPT_NONEG),
		OPT_BIT_F('b', "ignore-space-change", &options->xdl_opts,
			  N_("ignore changes in amount of whitespace"),
			  XDF_IGNORE_WHITESPACE_CHANGE, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-space-at-eol", &options->xdl_opts,
			  N_("ignore changes in whitespace at EOL"),
			  XDF_IGNORE_WHITESPACE_AT_EOL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-cr-at-eol", &options->xdl_opts,
			  N_("ignore carrier-return at the end of line"),
			  XDF_IGNORE_CR_AT_EOL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "ignore-blank-lines", &options->xdl_opts,
			  N_("ignore changes whose lines are all blank"),
			  XDF_IGNORE_BLANK_LINES, PARSE_OPT_NONEG),
		OPT_BIT(0, "indent-heuristic", &options->xdl_opts,
			N_("heuristic to shift diff hunk boundaries for easy reading"),
			XDF_INDENT_HEURISTIC),
		OPT_CALLBACK_F(0, "patience", options, NULL,
			       N_("generate diff using the \"patience diff\" algorithm"),
			       PARSE_OPT_NONEG | PARSE_OPT_NOARG,
			       diff_opt_patience),
		OPT_BITOP(0, "histogram", &options->xdl_opts,
			  N_("generate diff using the \"histogram diff\" algorithm"),
			  XDF_HISTOGRAM_DIFF, XDF_DIFF_ALGORITHM_MASK),
		OPT_CALLBACK_F(0, "diff-algorithm", options, N_("<algorithm>"),
			       N_("choose a diff algorithm"),
			       PARSE_OPT_NONEG, diff_opt_diff_algorithm),
		OPT_CALLBACK_F(0, "anchored", options, N_("<text>"),
			       N_("generate diff using the \"anchored diff\" algorithm"),
			       PARSE_OPT_NONEG, diff_opt_anchored),
		OPT_CALLBACK_F(0, "word-diff", options, N_("<mode>"),
			       N_("show word diff, using <mode> to delimit changed words"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_word_diff),
		OPT_CALLBACK_F(0, "word-diff-regex", options, N_("<regex>"),
			       N_("use <regex> to decide what a word is"),
			       PARSE_OPT_NONEG, diff_opt_word_diff_regex),
		OPT_CALLBACK_F(0, "color-words", options, N_("<regex>"),
			       N_("equivalent to --word-diff=color --word-diff-regex=<regex>"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG, diff_opt_color_words),
		OPT_CALLBACK_F(0, "color-moved", options, N_("<mode>"),
			       N_("moved lines of code are colored differently"),
			       PARSE_OPT_OPTARG, diff_opt_color_moved),
		OPT_CALLBACK_F(0, "color-moved-ws", options, N_("<mode>"),
			       N_("how white spaces are ignored in --color-moved"),
			       0, diff_opt_color_moved_ws),

		OPT_GROUP(N_("Other diff options")),
		OPT_CALLBACK_F(0, "relative", options, N_("<prefix>"),
			       N_("when run from subdir, exclude changes outside and show relative paths"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_relative),
		OPT_BOOL('a', "text", &options->flags.text,
			 N_("treat all files as text")),
		OPT_BOOL('R', NULL, &options->flags.reverse_diff,
			 N_("swap two inputs, reverse the diff")),
		OPT_BOOL(0, "exit-code", &options->flags.exit_with_status,
			 N_("exit with 1 if there were differences, 0 otherwise")),
		OPT_BOOL(0, "quiet", &options->flags.quick,
			 N_("disable all output of the program")),
		OPT_BOOL(0, "ext-diff", &options->flags.allow_external,
			 N_("allow an external diff helper to be executed")),
		OPT_CALLBACK_F(0, "textconv", options, NULL,
			       N_("run external text conversion filters when comparing binary files"),
			       PARSE_OPT_NOARG, diff_opt_textconv),
		OPT_CALLBACK_F(0, "ignore-submodules", options, N_("<when>"),
			       N_("ignore changes to submodules in the diff generation"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_ignore_submodules),
		OPT_CALLBACK_F(0, "submodule", options, N_("<format>"),
			       N_("specify how differences in submodules are shown"),
			       PARSE_OPT_NONEG | PARSE_OPT_OPTARG,
			       diff_opt_submodule),
		OPT_SET_INT_F(0, "ita-invisible-in-index", &options->ita_invisible_in_index,
			      N_("hide 'git add -N' entries from the index"),
			      1, PARSE_OPT_NONEG),
		OPT_SET_INT_F(0, "ita-visible-in-index", &options->ita_invisible_in_index,
			      N_("treat 'git add -N' entries as real in the index"),
			      0, PARSE_OPT_NONEG),
		OPT_CALLBACK_F('S', NULL, options, N_("<string>"),
			       N_("look for differences that change the number of occurrences of the specified string"),
			       0, diff_opt_pickaxe_string),
		OPT_CALLBACK_F('G', NULL, options, N_("<regex>"),
			       N_("look for differences that change the number of occurrences of the specified regex"),
			       0, diff_opt_pickaxe_regex),
		OPT_BIT_F(0, "pickaxe-all", &options->pickaxe_opts,
			  N_("show all changes in the changeset with -S or -G"),
			  DIFF_PICKAXE_ALL, PARSE_OPT_NONEG),
		OPT_BIT_F(0, "pickaxe-regex", &options->pickaxe_opts,
			  N_("treat <string> in -S as extended POSIX regular expression"),
			  DIFF_PICKAXE_REGEX, PARSE_OPT_NONEG),
		OPT_FILENAME('O', NULL, &options->orderfile,
			     N_("control the order in which files appear in the output")),
		OPT_CALLBACK_F(0, "find-object", options, N_("<object-id>"),
			       N_("look for differences that change the number of occurrences of the specified object"),
			       PARSE_OPT_NONEG, diff_opt_find_object),
		OPT_CALLBACK_F(0, "diff-filter", options, N_("[(A|C|D|M|R|T|U|X|B)...[*]]"),
			       N_("select files by diff type"),
			       PARSE_OPT_NONEG, diff_opt_diff_filter),
		{ OPTION_CALLBACK, 0, "output", options, N_("<file>"),
		  N_("Output to a specific file"),
		  PARSE_OPT_NONEG, NULL, 0, diff_opt_output },

		OPT_END()
	};

	ALLOC_ARRAY(options->parseopts, ARRAY_SIZE(parseopts));
	memcpy(options->parseopts, parseopts, sizeof(parseopts));
}

int diff_opt_parse(struct diff_options *options,
		   const char **av, int ac, const char *prefix)
{
	if (!prefix)
		prefix = "";

	ac = parse_options(ac, av, prefix, options->parseopts, NULL,
			   PARSE_OPT_KEEP_DASHDASH |
			   PARSE_OPT_KEEP_UNKNOWN |
			   PARSE_OPT_NO_INTERNAL_HELP |
			   PARSE_OPT_ONE_SHOT |
			   PARSE_OPT_STOP_AT_NON_OPTION);

	return ac;
	/* Do we want all 40 hex characters? */
	if (len == the_hash_algo->hexsz)
	/* An abbreviated value is fine, possibly followed by an ellipsis. */

	if (!print_sha1_ellipsis())
		return abbrev;

	 * In well-behaved cases, where the abbreviated result is the
	if (abblen < the_hash_algo->hexsz - 3) {
	    oideq(&one->oid, &two->oid) &&
		else if (!oideq(&p->one->oid, &p->two->oid) ||
static void show_file_mode_name(struct diff_options *opt, const char *newdelete, struct diff_filespec *fs)
	struct strbuf sb = STRBUF_INIT;
		strbuf_addf(&sb, " %s mode %06o ", newdelete, fs->mode);
		strbuf_addf(&sb, " %s ", newdelete);
	quote_c_style(fs->path, &sb, NULL, 0);
	strbuf_addch(&sb, '\n');
	emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
			 sb.buf, sb.len, 0);
	strbuf_release(&sb);
}
static void show_mode_change(struct diff_options *opt, struct diff_filepair *p,
		int show_name)
		struct strbuf sb = STRBUF_INIT;
		strbuf_addf(&sb, " mode change %06o => %06o",
			    p->one->mode, p->two->mode);
			strbuf_addch(&sb, ' ');
			quote_c_style(p->two->path, &sb, NULL, 0);
		strbuf_addch(&sb, '\n');
		emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
				 sb.buf, sb.len, 0);
		strbuf_release(&sb);
static void show_rename_copy(struct diff_options *opt, const char *renamecopy,
		struct diff_filepair *p)
	struct strbuf sb = STRBUF_INIT;
	struct strbuf names = STRBUF_INIT;

	pprint_rename(&names, p->one->path, p->two->path);
	strbuf_addf(&sb, " %s %s (%d%%)\n",
		    renamecopy, names.buf, similarity_index(p));
	strbuf_release(&names);
	emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
				 sb.buf, sb.len, 0);
	show_mode_change(opt, p, 0);
	strbuf_release(&sb);
		show_file_mode_name(opt, "delete", p->one);
		show_file_mode_name(opt, "create", p->two);
		show_rename_copy(opt, "copy", p);
		show_rename_copy(opt, "rename", p);
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, " rewrite ");
			quote_c_style(p->two->path, &sb, NULL, 0);
			strbuf_addf(&sb, " (%d%%)\n", similarity_index(p));
			emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
					 sb.buf, sb.len, 0);
			strbuf_release(&sb);
		show_mode_change(opt, p, !p->score);
	git_hash_ctx *ctx;
void flush_one_hunk(struct object_id *result, git_hash_ctx *ctx)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	unsigned short carry = 0;
	int i;

	the_hash_algo->final_fn(hash, ctx);
	the_hash_algo->init_fn(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < the_hash_algo->rawsz; ++i) {
		carry += result->hash[i] + hash[i];
		result->hash[i] = carry;
		carry >>= 8;
	}
}

	the_hash_algo->update_fn(data->ctx, line, new_len);
static void patch_id_add_string(git_hash_ctx *ctx, const char *str)
	the_hash_algo->update_fn(ctx, str, strlen(str));
static void patch_id_add_mode(git_hash_ctx *ctx, unsigned mode)
	the_hash_algo->update_fn(ctx, buf, len);
/* returns 0 upon success, and writes result into oid */
static int diff_get_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only, int stable)
	git_hash_ctx ctx;
	the_hash_algo->init_fn(&ctx);
	oidclr(oid);
		diff_fill_oid_info(p->one, options->repo->index);
		diff_fill_oid_info(p->two, options->repo->index);
		the_hash_algo->update_fn(&ctx, p->one->path, len1);
		the_hash_algo->update_fn(&ctx, p->two->path, len2);
			the_hash_algo->update_fn(&ctx, p->two->path, len2);
			the_hash_algo->update_fn(&ctx, p->one->path, len1);
			the_hash_algo->update_fn(&ctx, p->one->path, len1);
			the_hash_algo->update_fn(&ctx, p->two->path, len2);
		if (fill_mmfile(options->repo, &mf1, p->one) < 0 ||
		    fill_mmfile(options->repo, &mf2, p->two) < 0)
		if (diff_filespec_is_binary(options->repo, p->one) ||
		    diff_filespec_is_binary(options->repo, p->two)) {
			the_hash_algo->update_fn(&ctx, oid_to_hex(&p->one->oid),
					the_hash_algo->hexsz);
			the_hash_algo->update_fn(&ctx, oid_to_hex(&p->two->oid),
					the_hash_algo->hexsz);
		if (xdi_diff_outf(&mf1, &mf2, discard_hunk_line,
				  patch_id_consume, &data, &xpp, &xecfg))

		if (stable)
			flush_one_hunk(oid, &ctx);
	if (!stable)
		the_hash_algo->final_fn(oid->hash, &ctx);

int diff_flush_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only, int stable)
	int result = diff_get_patch_id(options, oid, diff_header_only, stable);
	fflush(stdout);
	if (0 < needed)
static void diff_flush_patch_all_file_pairs(struct diff_options *o)
{
	int i;
	static struct emitted_diff_symbols esm = EMITTED_DIFF_SYMBOLS_INIT;
	struct diff_queue_struct *q = &diff_queued_diff;

	if (WSEH_NEW & WS_RULE_MASK)
		BUG("WS rules bit mask overlaps with diff symbol flags");

	if (o->color_moved)
		o->emitted_symbols = &esm;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (check_pair_status(p))
			diff_flush_patch(p, o);
	}

	if (o->emitted_symbols) {
		if (o->color_moved) {
			struct hashmap add_lines, del_lines;

			if (o->color_moved_ws_handling &
			    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
				o->color_moved_ws_handling |= XDF_IGNORE_WHITESPACE;

			hashmap_init(&del_lines, moved_entry_cmp, o, 0);
			hashmap_init(&add_lines, moved_entry_cmp, o, 0);

			add_lines_to_move_detection(o, &add_lines, &del_lines);
			mark_color_as_moved(o, &add_lines, &del_lines);
			if (o->color_moved == COLOR_MOVED_ZEBRA_DIM)
				dim_moved_lines(o);

			hashmap_free_entries(&add_lines, struct moved_entry,
						ent);
			hashmap_free_entries(&del_lines, struct moved_entry,
						ent);
		}

		for (i = 0; i < esm.nr; i++)
			emit_diff_symbol_from_struct(o, &esm.buf[i]);

		for (i = 0; i < esm.nr; i++)
			free((void *)esm.buf[i].line);
		esm.nr = 0;

		o->emitted_symbols = NULL;
	}
}

	if (output_format & DIFF_FORMAT_DIRSTAT && options->flags.dirstat_by_line)
		compute_diffstat(options, &diffstat, q);
	    options->flags.exit_with_status &&
	    options->flags.diff_from_contents) {
		options->color_moved = 0;
			emit_diff_symbol(options, DIFF_SYMBOL_SEPARATOR, NULL, 0, 0);
			if (options->stat_sep)
				emit_diff_symbol(options, DIFF_SYMBOL_STAT_SEP,
						 NULL, 0, 0);
		diff_flush_patch_all_file_pairs(options);
	if (options->flags.diff_from_contents) {
			options->flags.has_changes = 1;
			options->flags.has_changes = 0;
static int diff_filespec_is_identical(struct repository *r,
				      struct diff_filespec *one,
	if (diff_populate_filespec(r, one, 0))
	if (diff_populate_filespec(r, two, 0))
static int diff_filespec_check_stat_unmatch(struct repository *r,
					    struct diff_filepair *p)
	    diff_populate_filespec(r, p->one, CHECK_SIZE_ONLY) ||
	    diff_populate_filespec(r, p->two, CHECK_SIZE_ONLY) ||
	    !diff_filespec_is_identical(r, p->one, p->two)) /* (2) */
		if (diff_filespec_check_stat_unmatch(diffopt->repo, p))
			if (!diffopt->flags.no_index)
void diffcore_fix_diff_index(void)
static void add_if_missing(struct repository *r,
			   struct oid_array *to_fetch,
			   const struct diff_filespec *filespec)
{
	if (filespec && filespec->oid_valid &&
	    !S_ISGITLINK(filespec->mode) &&
	    oid_object_info_extended(r, &filespec->oid, NULL,
				     OBJECT_INFO_FOR_PREFETCH))
		oid_array_append(to_fetch, &filespec->oid);
}

	if (options->repo == the_repository && has_promisor_remote()) {
		/*
		 * Prefetch the diff pairs that are about to be flushed.
		 */
		int i;
		struct diff_queue_struct *q = &diff_queued_diff;
		struct oid_array to_fetch = OID_ARRAY_INIT;

		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			add_if_missing(options->repo, &to_fetch, p->one);
			add_if_missing(options->repo, &to_fetch, p->two);
		}
		if (to_fetch.nr)
			/*
			 * NEEDSWORK: Consider deduplicating the OIDs sent.
			 */
			promisor_remote_get_direct(options->repo,
						   to_fetch.oid, to_fetch.nr);
		oid_array_clear(&to_fetch);
	}

			diffcore_break(options->repo,
				       options->break_opt);
	if (options->pickaxe_opts & DIFF_PICKAXE_KINDS_MASK)
	if (diff_queued_diff.nr && !options->flags.diff_from_contents)
		options->flags.has_changes = 1;
		options->flags.has_changes = 0;
	if (!opt->flags.exit_with_status &&
	if (opt->flags.exit_with_status &&
	    opt->flags.has_changes)
	    opt->flags.check_failed)
	return (opt->flags.quick &&
		opt->flags.has_changes);
	struct diff_flags orig_flags = options->flags;
	if (!options->flags.override_submodule_config)
	if (options->flags.ignore_submodules)
void compute_diffstat(struct diff_options *options,
		      struct diffstat_t *diffstat,
		      struct diff_queue_struct *q)
{
	int i;

	memset(diffstat, 0, sizeof(struct diffstat_t));
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (check_pair_status(p))
			diff_flush_stat(p, options, diffstat);
	}
}

	if (options->flags.reverse_diff)
	if (!options->flags.diff_from_contents)
		options->flags.has_changes = 1;
	if (options->flags.reverse_diff) {
	if (options->flags.diff_from_contents)
	if (options->flags.quick && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(options->repo, p))
	options->flags.has_changes = 1;
static char *run_textconv(struct repository *r,
			  const char *pgm,
			  struct diff_filespec *spec,
			  size_t *outsize)
	temp = prepare_temp_file(r, spec->path, spec);
size_t fill_textconv(struct repository *r,
		     struct userdiff_driver *driver,
		if (diff_populate_filespec(r, df, 0))
		BUG("fill_textconv called with non-textconv driver");
	*outbuf = run_textconv(r, driver->textconv, df, &size);
int textconv_object(struct repository *r,
		    const char *path,
	textconv = get_textconv(r, df);
	*buf_size = fill_textconv(r, textconv, df, buf);
	if (!opt->flags.exit_with_status &&