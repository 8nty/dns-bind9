############################################################################
# SPDX-License-Identifier: MPL-2.0

import sys

try:
    import yaml
except (ModuleNotFoundError, ImportError):
    print("No python yaml module, skipping")
    sys.exit(1)

import subprocess
import pprint

DNSTAP_READ = sys.argv[1]
DATAFILE = sys.argv[2]
ARGS = [DNSTAP_READ, '-y', DATAFILE]

with subprocess.Popen(ARGS, stdout=subprocess.PIPE) as f:
    for y in yaml.load_all(f.stdout, Loader=yaml.SafeLoader):
        pprint.pprint(y)
