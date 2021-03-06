#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "lrntree.h"

int main()
{
    LearnTree tree;
    tree.open ( DEFAULT_CHENARD_TREE_FILENAME );
    LearnBranch branch;

    for ( INT32 offset=0; tree.read(offset,branch); offset++ )
    {
        if ( branch.child == 0xffff )
            branch.child = -1;

        if ( branch.sibling == 0xffff )
            branch.sibling = -1;

        if ( branch.winsAndLosses & 0x8000 )
            branch.winsAndLosses |= 0xffff0000;

        tree.write ( offset, branch );
    }

    return 0;
}

void ChessFatal ( const char *msg )
{
    fprintf ( stderr, "%s\n", msg );
    exit(1);
}

/*
    $Log: fixtree.cpp,v $
    Revision 1.2  2006/03/20 20:44:10  dcross
    I finally figured out the weird slowness I have been seeing in Chenard accessing
    its experience tree.  It turns out it only happens the first time it accessed the file
    chenard.tre after a reboot.  It was caused by Windows XP thinking chenard.tre was
    an important system file, because of its extension:
    http://msdn.microsoft.com/library/default.asp?url=/library/en-us/sr/sr/monitored_file_extensions.asp
    We write 36 bytes to the middle of the file, then close it
    So I have changed the filename from chenard.tre to chenard.trx.
    I also added DEFAULT_CHENARD_TREE_FILENAME in lrntree.h so that I can more
    easily rename this again if need be.

    Revision 1.1  2005/11/25 19:47:27  dcross
    Recovered lots of old chess source files from the dead!
    Found these on CDROM marked "14 September 1999".
    Added cvs log tag and moved old revision history after that.

*/

