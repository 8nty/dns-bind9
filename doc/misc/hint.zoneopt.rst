.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

  zone <string> [ <class> ] {
  	type hint;
  	check-names ( fail | warn | ignore );
  	delegation-only <boolean>;
  	file <quoted_string>;
  };
