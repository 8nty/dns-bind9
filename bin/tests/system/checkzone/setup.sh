# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

. ../conf.sh

ln -s $CHECKZONE named-compilezone

./named-compilezone -D -F raw -o good1.db.raw example \
        zones/good1.db > /dev/null 2>&1
./named-compilezone -D -F map -o good1.db.map example \
        zones/good1.db > /dev/null 2>&1
