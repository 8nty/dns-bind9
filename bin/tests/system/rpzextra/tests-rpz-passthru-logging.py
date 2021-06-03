#!/usr/bin/python3
############################################################################
# SPDX-License-Identifier: MPL-2.0

import os
import pytest
import dns.resolver


# @pytest.mark.dnspython
def test_rpz_passthru_logging(named_port):
    resolver = dns.resolver.Resolver()
    resolver.nameservers = ['10.53.0.1']
    resolver.port = named_port

    # Should generate a log entry into rpz_passthru.txt
    ans = resolver.query('allowed.', 'A')
    for rd in ans:
        assert rd.address == "10.53.0.2"

    # baddomain.com isn't allowed (CNAME .), should return NXDOMAIN
    # Should generate a log entry into rpz.txt
    with pytest.raises(dns.resolver.NXDOMAIN):
        resolver.query('baddomain.', 'A')

    rpz_passthru_logfile = os.path.join("ns1", "rpz_passthru.txt")
    rpz_logfile = os.path.join("ns1", "rpz.txt")

    assert os.path.isfile(rpz_passthru_logfile)
    assert os.path.isfile(rpz_logfile)

    with open(rpz_passthru_logfile) as log_file:
        line = log_file.read()
        assert "rpz QNAME PASSTHRU rewrite allowed/A/IN" in line

    with open(rpz_logfile) as log_file:
        line = log_file.read()
        assert "rpz QNAME PASSTHRU rewrite allowed/A/IN" not in line
        assert "rpz QNAME NXDOMAIN rewrite baddomain/A/IN" in line
