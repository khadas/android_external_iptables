#ifndef _IP6TABLES_USER_H
#define _IP6TABLES_USER_H

#include "iptables_common.h"
#include "libiptc/libip6tc.h"

/* Include file for additions: new matches and targets. */
struct ip6tables_match
{
	struct ip6tables_match *next;

	ip6t_chainlabel name;

	const char *version;

	/* Size of match data. */
	size_t size;

	/* Function which prints out usage message. */
	void (*help)(void);

	/* Initialize the match. */
	void (*init)(struct ip6t_entry_match *m, unsigned int *nfcache);

	/* Function which parses command options; returns true if it
	   ate an option */
	int (*parse)(int c, char **argv, int invert, unsigned int *flags,
		     const struct ip6t_entry *entry,
		     unsigned int *nfcache,
		     struct ip6t_entry_match **match);

	/* Final check; exit if not ok. */
	void (*final_check)(unsigned int flags);

	/* Prints out the match iff non-NULL: put space at end */
	void (*print)(const struct ip6t_ip6 *ip,
		      const struct ip6t_entry_match *match, int numeric);

	/* Saves the union ipt_matchinfo in parsable form to stdout. */
	void (*save)(const struct ip6t_ip6 *ip,
		     const struct ip6t_entry_match *match);

	/* Pointer to list of extra command-line options */
	struct option *extra_opts;

	/* Ignore these men behind the curtain: */
	unsigned int option_offset;
	struct ip6t_entry_match *m;
	unsigned int mflags;
};

struct ip6tables_target
{
	struct ip6tables_target *next;
	
	ip6t_chainlabel name;

	const char *version;

	/* Size of target data. */
	size_t size;

	/* Function which prints out usage message. */
	void (*help)(void);

	/* Initialize the target. */
	void (*init)(struct ip6t_entry_target *t, unsigned int *nfcache);

	/* Function which parses command options; returns true if it
	   ate an option */
	int (*parse)(int c, char **argv, int invert, unsigned int *flags,
		     const struct ip6t_entry *entry,
		     struct ip6t_entry_target **target);
	
	/* Final check; exit if not ok. */
	void (*final_check)(unsigned int flags);

	/* Prints out the target iff non-NULL: put space at end */
	void (*print)(const struct ip6t_ip6 *ip,
		      const struct ip6t_entry_target *target, int numeric);

	/* Saves the targinfo in parsable form to stdout. */
	void (*save)(const struct ip6t_ip6 *ip,
		     const struct ip6t_entry_target *target);

	/* Pointer to list of extra command-line options */
	struct option *extra_opts;

	/* Ignore these men behind the curtain: */
	unsigned int option_offset;
	struct ip6t_entry_target *t;
	unsigned int tflags;
};

/* Your shared library should call one of these. */
extern void register_match6(struct ip6tables_match *me);
extern void register_target6(struct ip6tables_target *me);

extern int do_command6(int argc, char *argv[], char **table,
		       ip6tc_handle_t *handle);
/* Keeping track of external matches and targets: linked lists. */
extern struct ip6tables_match *ip6tables_matches;
extern struct ip6tables_target *ip6tables_targets;

extern struct ip6tables_target *find_target6(const char *name, int tryload);
extern struct ip6tables_match *find_match6(const char *name, int tryload);
#endif /*_IP6TABLES_USER_H*/