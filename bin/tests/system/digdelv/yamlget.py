############################################################################
# SPDX-License-Identifier: MPL-2.0

import sys

try:
    import yaml
# flake8: noqa: E722
# pylint: disable=bare-except
except:
    print("No python yaml module, skipping")
    sys.exit(1)

with open(sys.argv[1], "r") as f:
    for item in yaml.safe_load_all(f):
        for key in sys.argv[2:]:
            try:
                key = int(key)
            except ValueError:
                pass

            try:
                item = item[key]
            except KeyError:
                print('Key "' + key + '" not found.')
                sys.exit(1)

        print(item)
