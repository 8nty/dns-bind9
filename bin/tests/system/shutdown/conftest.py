############################################################################
# SPDX-License-Identifier: MPL-2.0

import os
import pytest


def pytest_configure(config):
    config.addinivalue_line(
        "markers", "dnspython: mark tests that need dnspython to function"
    )


def pytest_collection_modifyitems(config, items):
    # pylint: disable=unused-argument,unused-import,too-many-branches
    # pylint: disable=import-outside-toplevel

    # Test for dnspython module
    skip_dnspython = pytest.mark.skip(
        reason="need dnspython module to run")
    try:
        import dns.query  # noqa: F401
    except ModuleNotFoundError:
        for item in items:
            if "dnspython" in item.keywords:
                item.add_marker(skip_dnspython)


@pytest.fixture
def named_port(request):
    # pylint: disable=unused-argument
    port = os.getenv("PORT")
    if port is None:
        port = 5301
    else:
        port = int(port)

    return port


@pytest.fixture
def control_port(request):
    # pylint: disable=unused-argument
    port = os.getenv("CONTROLPORT")
    if port is None:
        port = 5301
    else:
        port = int(port)

    return port
