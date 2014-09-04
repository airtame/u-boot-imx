/*
 * (C) Copyright 2014 AIRTAME ApS
 * Attila Sukosd <attila@airtame.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <fuse.h>
#include <asm/errno.h>

union mac_t {
    char macchr[9];
    u32 macint[2];
};

static int conv_a_to_i(char *a) {
    int len = strlen(a);
    int i=0, num=0;
    int res = 0;

    for(i = 0; i < len; i++) {
        if (a[i] >= '0' && a[i] <= '9') {
            num = a[i] - '0';
        } else if (a[i] >= 'a' && a[i] <= 'f') {
            num = (a[i] - 'a')+10;
        } else if (a[i] >= 'A' && a[i] <= 'F') {
            num = (a[i] - 'A')+10;
        }
        res = res*0x10 + num;
    }
    return res;
}

static int extract_mac(char *const argv[], char *mac) {
    int i;
    char macstr[20];
    if (strlen(argv[0]) > 20)
        return -1;

    memcpy(macstr, argv[0], strlen(argv[0]));
    for(i=0;i<6;i++) {
        macstr[(i*3)+2] = 0;
        mac[i] = conv_a_to_i(macstr+(i*3));
    }

    return 1;
}

static int do_imxmac(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	const char *op = argc >= 2 ? argv[1] : NULL;
	int confirmed = argc >= 3 && !strcmp(argv[2], "-y");
	u32 bank, word, cnt, val;
	int ret, i;
    union mac_t mac;
    memset(mac.macchr, 0, 9);
    char readablemac[20];
    int readonly=1;

	argc -= 2 + confirmed;
	argv += 2 + confirmed;

    /* FIXME: these are hardcoded for i.MX6 MAC Fuses */
    bank = 4;
    word = 2;
    cnt = 2;

	if (!strcmp(op, "get")) {
		if (argc > 0)
			return CMD_RET_USAGE;

		for (i = 0; i < cnt; i++, word++) {
			ret = fuse_read(bank, word, &val);
			if (ret)
				goto err;
            mac.macint[i] = val;
		}
        sprintf(readablemac, "%02x:%02x:%02x:%02x:%02x:%02x", mac.macchr[0], mac.macchr[1], mac.macchr[2], mac.macchr[3], mac.macchr[4], mac.macchr[5]);
        setenv("wifimac", readablemac);

        printf("Read MAC from the FUSE: %02x:%02x:%02x:%02x:%02x:%02x\n", mac.macchr[0], mac.macchr[1], mac.macchr[2], mac.macchr[3], mac.macchr[4], mac.macchr[5]);
    } else if (!strcmp(op, "set")) {
		if (argc < 1 || argc > 1)
			return CMD_RET_USAGE;

        bank = 4;
        word = 2;

        /* Read out the fuse to see if it contains an address already */
        for (i = 0; i < cnt; i++, word++) {
            ret = fuse_read(bank, word, &val);
            if (ret)
                goto err;
            mac.macint[i] = val;
        }

        /* Check whether the addresses are empty */
        if (mac.macint[0] == 0 && mac.macint[1] == 0) {
            readonly = 0;
        }

        /* Extract the mac address from the argument */
        extract_mac(argv, mac.macchr);

        bank = 4;
        word = 2;
        if (readonly == 0) {
            printf("Burning %02x:%02x:%02x:%02x:%02x:%02x in the fuse...\n", mac.macchr[0], mac.macchr[1], mac.macchr[2], mac.macchr[3], mac.macchr[4], mac.macchr[5]);

            ret = fuse_prog(bank, word, mac.macint[0]);
            if (ret)
                goto err;

            ret = fuse_prog(bank, word+1, mac.macint[1]);
            if (ret)
                goto err;
        }

        bank = 4;
        word = 2;
        printf("Overriding %02x:%02x:%02x:%02x:%02x:%02x in the fuse...\n", mac.macchr[0], mac.macchr[1], mac.macchr[2], mac.macchr[3], mac.macchr[4], mac.macchr[5]);

        ret = fuse_override(bank, word, mac.macint[0]);
        if (ret)
            goto err;

        ret = fuse_override(bank, word+1, mac.macint[1]);
        if (ret)
            goto err;
        printf("Done.\n");
	} else {
		return CMD_RET_USAGE;
	}

	return 0;

err:
	puts("ERROR\n");
	return ret;
}

U_BOOT_CMD(
	imxmac, CONFIG_SYS_MAXARGS, 0, do_imxmac,
	"IMX MAC Address sub-system",
	     "get - Reads out the MAC from the FUSE\n"
	"imxmac set <mac> - Burn the MAC into the FUSE\n"
);
