.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

  primaries <string> [ port <integer> ] [ dscp
      <integer> ] { ( <primaries> | <ipv4_address>
      [ port <integer> ] | <ipv6_address> [ port
      <integer> ] ) [ key <string> ] [ tls
      <string> ]; ... };
