/* DYN76.C (c) Copyright Harold Grovesteen, 2010-2011                 */

   the Compatibility Parameter Block, which is in essence a R0-R15 register
   save area.  These macros ensure storage keys and accesses are checked for

//#define DYN76_DEBUG
//#define DYN76_DEBUG_FKEEPER
struct fkeeper
/* File Keeper lists.  New entries are added at the top of the list
   Because both lists are treated a single shared resource they utilize
   the same lock, nfile_lock, to control CPU (thread) access */

static struct fkeeper *fkpr_head = NULL;  /* Open file status list */
static unsigned char DCCascii_to_ebcdic[] =
static unsigned char DCCebcdic_to_ascii[] =
static void StrConverter (char * s, unsigned char * cct)
    while (s [i])
static void MemConverter (char * s, unsigned char * cct, int len)
    while (i < len)
/* File keeper list controls */
#define DO_FREE 1
#define NO_FREE 0
static void nfile_init ()
#define _open w32_hopen
#define _open hopen
/* WARNING: This function MUST be called with nfile_lock already locked */
static void AddFKByID (U32 id, struct fkeeper *item, struct fkeeper **list)
    /* struct fkeeper * head = list; */
    item->id = id;
    item->next = *list;
    *list = item;
#ifdef DYN76_DEBUG_FKEEPER
    LOGMSG("DF18: AddFKByID added id=%d at %X with next item at %X to list head=%X at %X\n",
           item->id, item, item->next, *list, list);
#endif
static struct fkeeper * FindFK (U32 id, struct fkeeper **list)
#ifdef DYN76_DEBUG_FKEEPER
    LOGMSG("DF18: FindFK id=%d in list head at=%X\n", id, list);
#endif
    fk = *list;          /* Search the list */
#ifdef DYN76_DEBUG_FKEEPER
    LOGMSG("DF18: FindFK list head points to first entry at %X\n", fk);
#endif
    while (fk)
#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: FindFK id=%d (0x%X) is at: %X\n", fk->id, fk->id, fk);
#endif
        if (fk->id == id)
static void RemoveFKByID (U32 id, struct fkeeper **list, int free_entry)
#ifdef DYN76_DEBUG_FKEEPER
    LOGMSG("DF18: RemoveFKByID id %d from list head at=%X\n", id, list);
    fk = *list;
    while (fk)
#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: RemoveFKByID id=%d (0x%X) is at: %X\n", fk->id, fk->id, fk);
#endif
        if (fk->id == id)
            {
            }
            {
                *list = fk->next;
            }
            if (free_entry)
            {
#ifdef DYN76_DEBUG_FKEEPER
                LOGMSG("DF18: RemoveFKByID freeing id=%d at: %X\n", fk->id, fk);
#endif
                free (fk);
            }
static int RemoveFKByName (char * filename)
{
    while (fk)
        if (strcmp (fk->filename, filename) == 0)
        {   /* Found the entry! */
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - orphan _close(%d)\n", fk->handle);
#endif
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - orphan _close result: %d\n", i);
#endif
            {
                i = errno;
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - orphan _close errno: %d\n", i);
#endif
                i = -1 * i;
            }
            else
            {
                {
                }
                {
                }
  R0  = Set to 0 prior to call,
        0/ int rename (char * oldname - char * newname);
        3/ int close  (char * filename);
  R2..R4 = Parameters, depending on function number
    int    res;                 /* I/O integer results */
#ifdef DYN76_DEBUG
    int    io_error = 0;        /* Saves the errno for log messages */
#endif

    if (nfile_init_req)





        if (R1 == 4 || R1 == 5)
        {   /* For read and write guest file descriptor is in pseudo R3 */
        }

#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: CFILE - looking for guest file descriptor %d\n", ghandle);
#endif
        fk = FindFK(ghandle, &fkpr_head);
#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: CFILE - guest file descriptor %d found at %X\n",
               ghandle, fk);
#endif
        {   /* Did not find the guest file descriptor.
               Treat it as if it were a bad host file handle */
            R15 = -1 * EBADF;
            set_reg(15,R15);
            return;
#ifdef DYN76_DEBUG_FKEEPER
/* The following 4 functions are always ready to attempt

    if (R1 == 9)
    {
        if (i == -1)


    if (R1 == 8)
        LOGMSG("DF18: CFILE - _close(%d)\n", handle);
        res = _close (handle);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _close result: %d\n", res);
#endif
        R15 = res;
        {   RemoveFKByID (fk->id, &fkpr_head, DO_FREE);

    /*------------------------*/

    if (R1 == 7)
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _commit(%d)\n", handle);
        res =  _commit (handle);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _commit result: %d\n", res);
#endif
#else /* ifdef __MSVC__ */

#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - fsync(%d)\n", handle);
#endif
        res = fsync (handle);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - fsync result: %d \n", res);
#endif
#endif /* ifdef __MSVC__ */
        if (res != 0)
        {
            res = errno;
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - fsync/_commit errno: %d \n", res);
#endif
            R15 = -1 * res;
        }
        else
        {
            R15 = res;
        }

    /*------------------------*/

        LOGMSG("DF18: CFILE - seek\n");
        get_reg(R3,3);  /* offset in bytes */
        get_reg(R4,4);  /* origin of the seek */
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _lseek(%d, %d, %d)\n", handle, (long)R3, (int)R4);
#endif
        res = _lseek (handle, (long)R3, (int)R4);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _lseek result: %d\n", res);
#endif
        if (res == -1)
        {
            res = errno;
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - _lseek errno: %d\n", res);
#endif
            R15 = -1 * res;
        }
        else
        {
            R15 = res;
        }


    if (R0 == 0)
        if (rfk == NULL)

        /* Set this state's id for the guest and increment

        R5 = restart_id++;        /* safely increment the id counter */
#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: CFILE - adding restart fkeeper to rst_head list\n");
#endif
        AddFKByID(R5, rfk, &rst_head);





        rfk = FindFK(R5, &rst_head);
    /*-------------------------------------------------------------*/

    if (R0 == 1)
        if (R1 == 0)
                   (rfk->oldname [rfk->data - 1] != 0))
                ARCH_DEP(wfetchc)
                    (&(rfk->oldname [rfk->data]),
                     0,
                     R2,
                     space_ctl,
                if (rfk->data >= 259)

    /*-------------------------------------------------------------*/

    if (R0 == 2)
        if (R1 <= 3)
            while ((rfk->data == 0)                        /* Starting */
                ARCH_DEP(wfetchc)
                    (&(rfk->filename [rfk->data]),
                     0,
                     R2,
                     space_ctl,
                if (rfk->data >= 259)

    /*---------------------------------------------------------------------*/

    if (R1 == 0)
    {
        LOGMSG("DF18: CFILE - rename\n");
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - rename(from='%s',to='%s')\n",
                rfk->oldname, rfk->filename);
#endif
        res = rename (rfk->oldname, rfk->filename);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - rename result: %d\n", res);
#endif
        if (res != 0)
        {
            res = errno;
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - rename errno: %d\n", res);
#endif
            R15 = -1 * res;
        }
        else
        {
            R15 = res;
        }

    /*------------------------*/

    if (R1 == 1)
        LOGMSG("DF18: CFILE - unlink\n");

#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _unkink('%s')\n", rfk->filename);
#endif
        res = _unlink (rfk->filename);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _unlink result: %d\n", res);
#endif
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - remove('%s')\n", rfk->filename);
        res = remove (rfk->filename);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - remove result: %d\n", res);
#endif
#endif
        if (res != 0)
        {
            res = errno;
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - remove/_unlink errno: %d\n", res);
#endif
            R15 = -1 * res;
        }
        else
        {
            R15 = res;
        }

    /*------------------------*/

    if (R1 == 2)
        LOGMSG("DF18: CFILE - open\n");

        if (R3 & 0x04)
        }
        {
        if (R3 & 0x40)
        {
        }
        LOGMSG("DF18: CFILE - _open('%s', 0x%X, 0%o)\n", rfk->filename, i, R4);
        res = _open (rfk->filename, i, (mode_t)R4);
#ifdef DYN76_DEBUG
        LOGMSG("DF18: CFILE - _open result: %d\n", res);
#endif
        if (res != -1)

            rfk->handle = res;  /* Save the host handle */

            /* Transfer the restart fkeeper to the open file fkeeper list */
#ifdef DYN76_DEBUG_FKEEPER
            LOGMSG("DF18: CFILE - removing  w/o freeing fkeeper from restart list rst_head\n");
#endif
            RemoveFKByID (rfk->id, &rst_head, NO_FREE);
            dolock(nfile_lock);
#ifdef DYN76_DEBUG_FKEEPER
            LOGMSG("DF18: CFILE - adding fkeeper to open file list with fkpr_head\n");
#endif
            AddFKByID(nfile_id++, rfk, &fkpr_head);
            LOGMSG("DF18: CFILE - opened guest file descriptor %d, host handle: %d\n",
                    rfk->id, rfk->handle);
            unlock(nfile_lock);

            R15 = rfk->id;
            set_reg(15,R15);
            rfk = NULL;
               fkeeper structure was linked to the fkeeper list to allow restart
               of the operation from the restart id.  Now that we have been
        }

            res = errno;
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - _open errno: %X\n", res);
#endif
            R15 = -1 * res;
            /* Note: during start of the interruptable open operation the
               fkeeper structure was linked to the fkeeper list to allow restart
               of the operation from the restart id.  On a failure to actually open

    /*-----------------------------*/

    if (R1 == 3)
    {
        LOGMSG("DF18: CFILE - orphan close: '%s'\n", rfk->filename);


    /*-----------------------------*/

    if (R1 == 4)
        LOGMSG("DF18: CFILE - read\n");
        while (R4 != 0)
            if (rfk->data == 0)
            { /* Need to fill our buffer with some data? */

                if (i > 256)

            {   /* All done, we reached EOF (or an error occured) */
            }
            /* wstorec was designed to operate with storage-to-storage instructions.
               The instruction length field is always one less than the number of
               bytes involved in the instruction.  Hence the number of bytes to be
               moved to storage is decremented by 1 to conform with this behavior. */

            /* WARNING: This is where an interruption might occur.  An exception
               will "nullify" the storing operation.
               On restart, the read above will be bypassed and the entire sequence
               of bytes, upto 256, will be restored */
            ARCH_DEP(wstorec)
                 (unsigned char)i,
                 R2,
                 space_ctl,





    /*-----------------------------*/

    if (R1 == 5)
        LOGMSG("DF18: CFILE - write\n");
        while (R4 != 0)
            /* wfetchc was designed to operate with storage-to-storage instructions.
               The instruction length field is always one less than the number of
               bytes involved in the instruction.  Hence the number of bytes to be
               retrieved from storage  is decremented by 1 to conform with this
               behavior. */
            if (i > 255)
            {
            }

            /* WARNING: This is where interruption might occur.  The exception
               "nullifies" the fetch operation.
               On restart, the entire sequence of up to 256 bytes will be refetched
               from storage */
            ARCH_DEP(wfetchc)
                (rfk->filename,
                 (unsigned char)i,
                 R2,
                 space_ctl,
                 regs);
            i++;  /* Fix up number of bytes stored to actual count */

#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - _write(%d, rfk->filename, %d)\n", handle, i);
#endif
            res = _write (handle, rfk->filename, (size_t)i);
#ifdef DYN76_DEBUG
            LOGMSG("DF18: CFILE - _write result: %d\n", res);
#endif
            if (res < 0)
#ifdef DYN76_DEBUG
                io_error = errno;
                LOGMSG("DF18: CFILE - write errno: %d\n", io_error);
#endif
            }

            /* Not an error, so 'res' is the number of bytes actually written */
            /* Update the address pointer and remaining bytes to write */
            R2 += res;
            set_reg(2,R2);
            R4 -= res;
            set_reg(4,R4);
            /* update the accumlated total */
            R15 += res;
        R5 = rfk->SaveArea;

    {
#ifdef DYN76_DEBUG_FKEEPER
        LOGMSG("DF18: CFILE - removing and freeing restart fkeeper in rst_head list\n");
#endif
        /* Safely remove from the restart state */
        RemoveFKByID (rfk->id, &rst_head, DO_FREE);
    }

#endif
#endif