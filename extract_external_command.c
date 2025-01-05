#include "main.h"

void extract_external_commands(char **external_commands)
{
   // List of commands
    char *commands[] = {
        "bash", "bunzip2", "busybox", "bzcat", "bzcmp", "bzdiff",
        "bzegrep", "bzexe", "bzfgrep", "bzgrep", "bzip2", "bzip2recover",
        "bzless", "bzmore", "cat", "chacl", "chgrp", "chmod", "chown",
        "chvt", "cp", "cpio", "dash", "date", "dbus-cleanup-sockets",
        "dbus-daemon", "dbus-uuidgen", "dd", "df", "dir", "dmesg",
        "dnsdomainname", "domainname", "dumpkeys", "echo", "ed", "egrep",
        "false", "fgconsole", "fgrep", "findmnt", "fuser", "fusermount",
        "getfacl", "grep", "gunzip", "gzexe", "gzip", "hostname", "ip",
        "kbd_mode", "kill", "kmod", "less", "lessecho", "lessfile",
        "lesskey", "lesspipe", "ln", "loadkeys", "login", "loginctl",
        "lowntfs-3g", "ls", "lsblk", "lsmod", "mkdir", "mknod", "mktemp",
        "more", "mount", "mountpoint", "mt", "mt-gnu", "mv", "nano",
        "nc", "nc.openbsd", "netcat", "netstat", "nisdomainname",
        "ntfs-3g", "ntfs-3g.probe", "ntfs-3g.secaudit", "ntfs-3g.usermap",
        "ntfscat", "ntfsck", "ntfscluster", "ntfscmp", "ntfsdump_logfile",
        "ntfsfix", "ntfsinfo", "ntfsls", "ntfsmftalloc", "ntfsmove",
        "ntfstruncate", "ntfswipe", "open", "openvt", "pidof", "ping",
        "ping6", "plymouth", "plymouth-upstart-bridge", "ps", "pwd",
        "rbash", "readlink", "red", "rm", "rmdir", "rnano",
        "running-in-container", "run-parts", "sed", "setfacl", "setfont",
        "setupcon", "sh", "sh.distrib", "sleep", "ss", "static-sh", "stty",
        "su", "sync", "tailf", "tar", "tempfile", "touch", "true",
        "udevadm", "ulockmgr_server", "umount", "uname", "uncompress",
        "unicode_start", "vdir", "vmmouse_detect", "which", "whiptail",
        "ypdomainname", "zcat", "zcmp", "zdiff", "zegrep", "zfgrep",
        "zforce", "zgrep", "zless", "zmore", "znew", NULL
    };

    // Assign pointers
    int i;
    for (i = 0; commands[i] != NULL; i++) {
        external_commands[i] = commands[i]; // Point to commands
    }
    external_commands[i] = NULL; // Null-terminate

    // Print to verify
    // for (int j = 0; external_commands[j] != NULL; j++) {
    //     printf("%s\n", external_commands[j]);
    // }
}