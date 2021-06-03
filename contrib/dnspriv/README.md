<!-- SPDX-License-Identifier: MPL-2.0 -->
### DNS Privacy in BIND

This directory contains sample configuration files to enable BIND,
with Nginx as a TLS proxy, to provide DNS over TLS.

`named.conf` configures a validating recursive name server to listen
on the localhost address at port 8853.

`nginx.conf` configures a TLS proxy to listen on port 853 and
forward queries and responses to `named`.

For more information, please see
[https://dnsprivacy.org/wiki/](https://dnsprivacy.org/wiki/)
