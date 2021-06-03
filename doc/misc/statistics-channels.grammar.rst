.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

  statistics-channels {
  	inet ( <ipv4_address> | <ipv6_address> |
  	    * ) [ port ( <integer> | * ) ] [
  	    allow { <address_match_element>; ...
  	    } ];
  };
