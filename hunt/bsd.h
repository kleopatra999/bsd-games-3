/*
 *  Hunt
 *  Copyright (c) 1985 Conrad C. Huang, Gregory S. Couch, Kenneth C.R.C. Arnold
 *  San Francisco, California
 */

# if defined(BSD_RELEASE) && BSD_RELEASE >= 43
# define	BROADCAST
# define	SYSLOG_43
  # ifdef linux
    # define	TALK_42
  # else
    # define	TALK_43
  # endif
# endif
# if defined(BSD_RELEASE) && BSD_RELEASE == 42
# define	SYSLOG_42
# define	TALK_42
# endif
