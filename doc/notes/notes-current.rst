.. 
   Copyright (C) Internet Systems Consortium, Inc. ("ISC")
   
   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.
   
   See the COPYRIGHT file distributed with this work for additional
   information regarding copyright ownership.

Notes for BIND 9.17.3
---------------------

Security Fixes
~~~~~~~~~~~~~~

- None.

Known Issues
~~~~~~~~~~~~

- None.

New Features
~~~~~~~~~~~~

- ``rndc`` has been updated to use the new BIND network manager API.
  This change had the side effect of altering the TCP timeout for RNDC
  connections from 60 seconds to the ``tcp-idle-timeout`` value, which
  defaults to 30 seconds. Also, because the network manager currently
  has no support for UNIX-domain sockets, those cannot now be used
  with ``rndc``. This will be addressed in a future release, either by
  restoring UNIX-domain socket support or by formally declaring them
  to be obsolete in the control channel. [GL #1759]

Feature Changes
~~~~~~~~~~~~~~~

- New ``rndc`` command ``rndc dnssec -status`` that shows the current
  DNSSEC policy and keys in use, the key states and rollover status.
  [GL #1612]

- Disable and disallow static linking of BIND 9 binaries and libraries
  as BIND 9 modules require ``dlopen()`` support and static linking also
  prevents using security features like read-only relocations (RELRO) or
  address space layout randomization (ASLR) which are important for
  programs that interact with the network and process arbitrary user
  input. [GL #1933]

- As part of an ongoing effort to use RFC 8499 terminology, ``primaries``
  can now be used as a synonym for ``masters`` in ``named.conf``.
  Similarly, ``notify priamry-only`` can now be used as a synonym
  for ``notify master-only``. The output of ``rndc zonestatus`` now
  uses ``primary`` and ``secondary`` terminology. [GL #1948]

Bug Fixes
~~~~~~~~~

- Addressed an error in recursive clients stats reporting.
  There were occasions when an incoming query could trigger a prefetch for
  some eligible rrset, and if the prefetch code were executed before recursion,
  no increment in recursive clients stats would take place. Conversely,
  when processing the answers, if the recursion code were executed before the
  prefetch, the same counter would be decremented without a matching increment.
  [GL #1719]

- The DS set returned by ``dns_keynode_dsset()`` was not thread-safe.
  This could result in an INSIST being triggered. [GL #1926]

- The ``primary`` and ``secondary`` keywords, when used as parameters for
  ``check-names``, were not processed correctly and were being ignored.
  [GL #1949]

- 'rndc dnstap -roll <value>' was not limiting the number of saved
  files to <value>. [GL !3728]

- The validator could fail to accept a properly signed RRset if an
  unsupported algorithm appeared earlier in the DNSKEY RRset than a
  supported algorithm.  It could also stop if it detected a malformed
  public key. [GL #1689]

- The ``blackhole`` ACL was inadvertently disabled with respect to
  client queries. Blocked IP addresses were not used for upstream
  queries but queries from those addresses could still be answered.
  [GL #1936]

- ``named`` would crash on shutdown when new ``rndc`` connection is received at
  the same time as shutting down. [GL #1747]

- Fix assertion failure when server is under load and root zone is not yet
  loaded. [GL #1862]

- ``named`` could crash when cleaning dead nodes in ``lib/dns/rbtdb.c`` that
  have been reused meanwhile.  [GL #1968]

- The introduction of KASP support broke whether the second field
  of sig-validity-interval was treated as days or hours. (Thanks to
  Tony Finch.) [GL !3735]