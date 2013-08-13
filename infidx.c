/*===========================================================================
 * INFIDX
 *
 * -----ABSTRACT-------------------------------------------------------------
 * A program to open an INF-file from a user configurable selection-listbox
 * of all INF-files.
 *
 * -----PURPOSE--------------------------------------------------------------
 * As I have much of my INF-files on a removable MO-disk, I don't
 * want to create static WPS-objects for them, but I need a way to
 * decect dynamically which INF-files are there and display only these ones.
 * (Is the disk insertet or not?)
 *
 * Other advanteges are:
 *  - fixed screen portion needed (independent of number of INF-files)
 *  - order/sorting determined by user (order of dirs in BOOKSHELF and order
 *    of entries in the config files)
 *  - the setup is easily ported over all reinstallations, as it is done in
 *    plain text files
 *  - you can add your own (longer) titles to the INF-files in the list
 *
 * This program is to fullfill this job. It will search in all directories
 * listed in the environment variable BOOKSHELF for a file called 'infidx'.
 * These configuration files must hold the name and a description for all
 * the INF-files that are to be shown in the selection list. There may reside
 * one 'infidx'-file in each scanned directory and the contents of all of them
 * is shown in the list in the order the entries are read.
 *
 * -----INSTALLATION---------------------------------------------------------
 * This is a standalone program (no entries in INI-files no DLL). All you need
 * is the EXE (in your PATH) and the following setup:
 *  - Add all the directories containing your INF-files to the environment
 *    variable BOOKSHELF.
 *    NOTE: - Order matters. The directories are scanned in this order and by
 *            this the directory of the INF-files you need most often should
 *            come first.
 *          - It is save to name not (allways) available drives/directories
 *            like A:.
 *  - Create a configuration file in all directories named in BOOKSHELF.
 *    (see "infidx-FILE_FORMAT")
 *    NOTE: -- Not all directories MUST have a config file.
 *          -- It is possible to have absolute pathes in the config files and
 *             let them refere to INF-files not in the directory of the
 *             config-file, but this is NOT recommended. By this you would
 *             have spread the information where your INF-files are located
 *             and a movement of the files would make it neccessary to edit
 *             the config-files too and not just adjust BOOKSHELF.
 *  - Positioning of the list on screen.
 *    The dialog with the list will startup at a fixed position. This position
 *    defaults to the lower left corner of the screen (coordinates 0,0).
 *    You can change the position in two ways:
 *    - Set an environment variable by     "set INFIDX=yourx,youry"
 *    - Invoke the program with arguments  "infidx yourx youry"
 *
 * -----INVOCATION-----------------------------------------------------------
 * Start the program by:
 *      infidx [yourx youry]
 * (See INSTALLATION about the parameters.)
 *
 * -----USING----------------------------------------------------------------
 * The program interfaces the user with a dialog. This dialog contains a
 * listbox, and four buttons (OPEN, EXIT, REINIT and ABOUT).
 *
 * To view an INF-file, select the corresponding entry in the listbox and push
 * the OPEN button.
 *
 * To exit the program just push the EXIT button.
 *
 * To rebuild the list after any changes made by you (changes of a config file
 * or media changes in drives in your BOOKSHELF-path).
 *
 * -----infidx-FILE_FORMAT---------------------------------------------------
 * These files can hold entry- and comment-lines. A comment-line starts with
 * a '#' in the first column. All other lines are interpreted as entry-lines.
 * An entry-line must hold at least two 'words'. The first word ist the param
 * given to view (the name of the INF-file. All other words are the title that
 * will be displayed in the list.
 *
 * Entry-lines are processed in the following way:
 *  - remove trailing white-space
 *  - skip leading white-space
 *  - store the first sequence of non-white-space-characters as the argument
 *    that will be passed to VIEW.EXE if this entry is selected
 *    (You must not include the path of an INF-file, if it resides in the
 *     same directory as the 'infidx'-file just processed, as a change dir to
 *     this place will take place on the start of this entry.)
 *  - skip the white-space following this first 'word'
 *  - store the rest of the line as the entry-text to be shown in the list
 *
 * Sample-entry-lines
 *   GG243730.INF                  Redbook 1 Control Program (general info)
 *   GG243730.INF+GG243731.INF     Redbook 1 & 2
 *   G:\BOOK.ADD\GG243730.INF      Redbook 1 Control Program (general info)
 *
 * -----LIMITS---------------------------------------------------------------
 * The program can only handle 300 entries at all. To increase this value
 * change the define in the header and recompile.
 *
 * -----IMPLEMENTATION-------------------------------------------------------
 * This is a one day program and this shows the source. Do not blame me for the
 * layout, grouping and endless functions. I wanted this program and I wanted
 * to build it with C++ and a the IBM GUI-class-lib. But hello-world was over
 * 500K in size after the half of this day. So I had to switch back to C-mode
 * and hand made PM-calls on the run. (I hope XVT will lead to smaller EXE's
 * in the future.)
 *
 * The program is made of a window and a dialog.
 * The window does no user interaction, but is resposible for:
 * - scanning the config-files
 * - starting the view processes (via system("start /N view param"))
 * - starting the dialog
 * The dialog does all the user interaction.
 *
 * The building environment:
 * - OS/2 2.1 GA (de)
 * - IBM C/C++ Set/2 (beta B4)
 * - TOOLKIT-20
 * - LINK386 (version 2.01.005,  16.3.93)
 * - NMAKE   (version 2.001.000, 11.2.93)
 *
 * -----LICENCE--------------------------------------------------------------
 * This program may be used for free. You may distribute the WHOLE packet
 * UNMODIFIED for any NONCOMERCIAL purpose.
 * The source code is primaly supplied to allow recompilations for other
 * OS/2 versions (if it is necessary at all). It although makes bugfixes and 
 * enhancements possible. If you do something of the later please send the
 * CHANGES TO ME, so that I can merge them in and release them. I would not
 * like you to make any changes and distribute the program under the same
 * name. You may use the code as a base for own developments but it would
 * be nice to MENTION MY NAME.
 *
 * Just use it!
 *
 * -----DISCLAIMER-----------------------------------------------------------
 * THIS PROGRAM DOES NOT FULLFILL ANY TASK AT ALL. THE ONLY GUARANTEE GIVEN
 * IS, THAT THE PROGRAM WILL DAMAGE AND DESTROY THE HARDWARE AND SOFTWARE IT
 * IS RUN ON. THE AUTHOR (THATS ME) IS NOT LIABLE FOR ANY LOSS YOU GET AS THE
 * RESULT OF USING THIS PROGRAM.
 *
 * -----HISTORY--------------------------------------------------------------
 * $Log:	infidx.c $
 *Revision 1.4  93/07/03  18:41:43  UWE
 *- seperated the program version number from the RCS revision
 *- added a licence and disclaimer to the documentation
 *
 *Revision 1.3  93/07/03  09:33:21  UWE
 *Fixed memory leak.
 *On REINIT the allocated memory for the list elements was not free()'ed.
 *initSelTable() & exitSelTable()  splitted:
 *initSelTable(): only set all pointers to NULL (called once in main
 *freeSelTable(): free all not NULL pointers in list (former exitSelTable()
 *                called at first in fillSelTable() and on exit
 *fillSelTable(): free any allocated memory and build list new with alloc()
 *-
 *Now compiled with IBM C++ GA version and Toolkit 2.1.
 *
 *Revision 1.2  93/07/02  11:09:52  UWE
 *Added positioning possibility by user and REINIT-button.
 *
 *Revision 1.1  93/07/01  22:08:20  UWE
 *Initial revision
 *
 * 
 *===========================================================================*/

static char *rcsid = "$Revision: 1.4 $ $Date: 93/07/03 18:41:43 $";

/*
 * C-library-declarations
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

/*
 * OS/2 system declarations
 */
#define INCL_BASE
#define INCL_PM
#include <os2.h>

/*
 * program declarations (only defines used by compiler and resource compiler)
 */
#include "infidx.h"

static char szAreaClientClass[]  = "infidx-area";    /* window class names */

static int startupdrive = 3;


/*==============================================================*/
/* ERROR-display message box                                    */
/*==============================================================*/
void errmsgbox( HWND hwnd,   /* hwnd of calling window */
                char *txt1,  /* these texts are displayed */
                char *txt2 ) {
  static char errmsg[500];
  (void)strcpy ( errmsg, "ERROR\n" );
  (void)strncat( errmsg, txt1, sizeof(errmsg) - strlen(errmsg) - 5 );
  (void)strcat ( errmsg, "\n" );
  (void)strncat( errmsg, txt2, sizeof(errmsg) - strlen(errmsg) - 5 );
  (void)WinMessageBox( HWND_DESKTOP,
                     hwnd,
                     errmsg,
                     PROGNAME,
                     0,                           /* ID does not matter */
                     MB_OK         | MB_ICONEXCLAMATION |
                     MB_DEFBUTTON1 | MB_MOVEABLE      );
  return;
}

/*============================================================*/
/* Window-procedure for the selection-dialog                  */
/*                                                            */
/* THIS FUNCTION AND THE CORESPONDING TYPES AND VARIABLES ARE */
/* USED BY seldialog(). THEY MUST NOT BE USED FROM ELSEWHERE  */
/*                                                            */
/* The dialog is made of a listbox and an buttons.            */
/*                                                            */
/* The list box handling is down by the default procedures.   */
/* All we have to do is to                                    */
/* - fill the list box on creation,                           */
/* - wait for a button to be pressed,                         */
/* - detect which button it was                               */
/* - query whether and which listentry was selected           */
/* - map the listentry to a index                             */
/* - return the user selection                                */
/*                                                            */
/* Return:                                                    */
/*   UK_CANCEL      = no entry selected ( CANCEL )            */
/*   else           = index of the selected entry             */
/*============================================================*/

typedef struct {
  int   index;
  int   drive;
  char  *param;
  char  *wdir;
  char  *text;
} _UK_SEL_TABLE;

static _UK_SEL_TABLE _uk_sel_table[UK_MAX_ENTRIES];

/***********************************************************************/
static void initSelTable( void )
{
  int  i;

  /*
   * init to defined state for later free without thinking
   */
  for (i=0; i<UK_MAX_ENTRIES; i++)
    {
      _uk_sel_table[i].index = (ULONG)i;
      _uk_sel_table[i].param = (char *)NULL;
      _uk_sel_table[i].wdir  = (char *)NULL;
      _uk_sel_table[i].text  = (char *)NULL;
    }
  return;
}

/***********************************************************************/
static void freeSelTable(void) {
  int i;

  /*
   * free all allocated memory
   */
  for (i=0; i<UK_MAX_ENTRIES; i++)
    {
      if (_uk_sel_table[i].param != (char *)NULL) (void)free(_uk_sel_table[i].param);
      if (_uk_sel_table[i].wdir  != (char *)NULL) (void)free(_uk_sel_table[i].wdir );
      if (_uk_sel_table[i].text  != (char *)NULL) (void)free(_uk_sel_table[i].text );
    }
}


/***********************************************************************/
static UK_RET fillSelTable( HWND hwnd )  /* only needed for errmsgbox() */
{
  int  i, len, index;
  char *envpath, *parsep, *cwd, *cp1, *cp2;
  char actpath[_MAX_PATH * 3];
  char conffile[_MAX_PATH * 3];
  FILE *conf;
  char line[1000];

  /*
   * free any allocated mem first
   */
  freeSelTable();

  /*
   * get path from environment
   */
  if ( (envpath = getenv( ENVVARNAME )) == (char *)NULL )
    {
      errmsgbox( hwnd, "Environment variable not set.", ENVVARNAME );
      return UK_ERR;
    }

  /*
   * loop over all entries in envpath
   */
  index = 0; /* let index be the next index to fill, that is one less as entries in list */
  for (parsep=envpath; (index < UK_MAX_ENTRIES) && ((*parsep) != '\0') ; /* do nothing */ )
    {
      /*
       * copy next entry from envpath to actpath
       */
      for ( i=0;
               (i < _MAX_PATH)
            && (*parsep != '\0')
            && (*parsep != ';');
            i++, parsep++ )
          actpath[i] = *parsep;
      actpath[i] = '\0';
      if ( *parsep == ';' )
          parsep++;
      /* make actpath a full path with drive */
      if ( actpath[1] != ':' )
        { /* no drive; shift path by 2 and insert drive */
          for (i=strlen(actpath); i>=0; i--)
              actpath[i+2] = actpath[i];
          actpath[1] = ':';
          actpath[0] = _getdrive() - 1 + 'A';
        } /* no drive */
      if ( actpath[2] != '\\' )
        { /* relative path */
          if ( (cwd = _getcwd((char *)NULL, _MAX_PATH)) != (char *)NULL )
            {
              len = strlen(cwd);
              if ( cwd[len-1] == '\\' )
                  len--;
              /* shift relative path by length of cwd incl. \\ */
              for (i=strlen(actpath); i>=2; i--)
                  actpath[i+len] = actpath[i];
              /* fill in the cwd */
              for (i=0; i<len; i++)
                  actpath[i+2] = cwd[i];
              actpath[len+2] = '\\';
              (void)free(cwd);
            }
        } /* relative path */
      /* copy actpath to conffile */
      (void)strcpy( conffile, actpath );
      /* add trailing \\ if neccessary */
      len = strlen(conffile);
      if ( conffile[len-1] != '\\' )
        {
          conffile[len] = '\\';
          len++;
          conffile[len] = '\0';
        }
      /* add our config file name to actpath */
      (void)strcat( conffile, CONFNAME );

      /*
       * open config file (if any)
       */
      if ( (conf = fopen( conffile, "r")) != (FILE *)NULL )
        { 
          while (  (index < UK_MAX_ENTRIES)
                && (fgets( line, sizeof(line), conf) != (char *)NULL )
                )
            {
              /* strip trailing white space */
              for ( cp1 = (strlen(line) == 0) ? line : (line + strlen(line) - 1);
                    (cp1 >= line) && ( (*cp1 == ' ') || (*cp1 == '\t') || (*cp1 == '\n') );
                    cp1-- )
                  *cp1 = '\0';
              /* position cp1 on first non white space */
              for ( cp1 = line;
                       (*cp1 != '\0')
                    && ( (*cp1 == ' ') || (*cp1 == '\t') );
                    cp1++ )
                  ; /* do nothing in loop body */
              /* search end of first word; end it by \0 and let cp2 point to rest of line */
              for ( cp2 = cp1;
                    (*cp2 != '\0') && (*cp2 != '\t') && (*cp2 != ' ');
                    cp2++ )
                  ; /* do nothing in loop body */
              if (  ( *cp2 != '\0' ) /* implies *cp1 != '\0' */
                 && ( *cp1 != '#'  )
                 )
                {
                  *cp2 = '\0';
                  for ( cp2++;
                           (*cp2 != '\0')
                        && ( (*cp2 == ' ') || (*cp2 == '\t') );
                        cp2++ )
                      ; /* do nothing in loop body */
                  if ( *cp2 != '\0' )
                    { /* cp1 and cp2 are in position */
                      /*
                       * fill entry in table ******************
                       */
                      if ( (_uk_sel_table[index].param = (char *)malloc(strlen(cp1)+1))
                         == (char *)NULL )
                        {
                          (void)fclose(conf);
                          errmsgbox( hwnd, "Out of memory", "malloc()" );
                          return UK_ERR;
                        }
                      (void)strcpy(_uk_sel_table[index].param, cp1);
                      if ( (_uk_sel_table[index].wdir  = (char *)malloc(strlen(actpath)+1))
                         == (char *)NULL )
                        {
                          (void)fclose(conf);
                          errmsgbox( hwnd, "Out of memory", "malloc()" );
                          return UK_ERR;
                        }
                      (void)strcpy(_uk_sel_table[index].wdir , actpath);
                      if ( (_uk_sel_table[index].text  = (char *)malloc(strlen(cp2)+1))
                         == (char *)NULL )
                        {
                          (void)fclose(conf);
                          errmsgbox( hwnd, "Out of memory", "malloc()" );
                          return UK_ERR;
                        }
                      (void)strcpy(_uk_sel_table[index].text , cp2);
                      _uk_sel_table[index].drive = toupper(_uk_sel_table[index].wdir[0]) - 'A' + 1;
                      index++;
 
                    } /* cp1 and cp2 are in position */
                } /* more than one word in line */
            } /* loop over lines in file */
          (void)fclose(conf);
        } /* can open file */
    } /* loop over entries in envpath */
  
  /*
   * at least one entry in list ?
   */
  if ( index <= 0 )
    {
      errmsgbox( hwnd, "No config file (" CONFNAME ") found in direcories of",
                        ENVVARNAME " or none holds a valid entry." );
      return UK_ERR;
    }

  /*
   * all entries read or list full ?
   */

  /*
   * if we get to this point all went well
   */
  if ( index == UK_MAX_ENTRIES )
    {
      errmsgbox( hwnd, "Reached maximum number of allowed entries.",
                       "(Proceeding with incomplete list.)" );
    }
  return UK_OK;
}


MRESULT EXPENTRY ukseldlg( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
  HWND  lboxhwnd;
  LONG  index;
  int   i;
  char  aboutmsg[300];

  switch ( msg )
    {
    case WM_INITDLG:
      lboxhwnd = WinWindowFromID( hwnd, UK_SEL_LBOX );
      for ( i = 0;
            (i < UK_MAX_ENTRIES) && (_uk_sel_table[i].param != (char *)NULL);
            i++ )
        {
          (void)WinInsertLboxItem( lboxhwnd, 
                                   LIT_END, 
                                   (PSZ)(_uk_sel_table[i].text) );
        }
      return( (MRESULT)FALSE );

    case WM_COMMAND:
      switch (LOUSHORT( mp1 ))  /* the ID of the window generating this cmd */
        {
        case UK_SEL_OPEN:         /* OPEN-push-button */
          lboxhwnd = WinWindowFromID( hwnd, UK_SEL_LBOX );
          index = WinQueryLboxSelectedItem( lboxhwnd );
          if ( index != LIT_NONE )
            {
              (void)WinDismissDlg( hwnd, _uk_sel_table[ index ].index );
              return( (MRESULT)0 );
            }
          /* show a little help */
          (void)WinMessageBox( HWND_DESKTOP,
                             hwnd,
                             "You must select an entry and push OPEN to view\n"
                             "an entry, push EXIT to end the program or\n"
                             "push REINIT to rebuild the list.",
                             PROGNAME,
                             0,                           /* ID does not matter */
                             MB_OK         | MB_ICONEXCLAMATION |
                             MB_DEFBUTTON1 | MB_MOVEABLE      );
          return( (MRESULT)0 );

        case UK_SEL_CANCEL:     /* CANCEL-push-button */
          (void)WinDismissDlg( hwnd, UK_CANCEL );
          return( (MRESULT)0 );

        case UK_SEL_REINIT:     /* REINIT-push-button */
          (void)WinDismissDlg( hwnd, UK_REINIT );
          return( (MRESULT)0 );

        case UK_SEL_ABOUT:      /* ABOUT-push-button */
          /* show version string */
          (void)sprintf(aboutmsg,
                        "by Uwe Koenzen (email: uk@acs451.GEI-Aachen.de)\nVersion %s (internal: %s)",
                        UKVERSION,
                        rcsid );
          (void)WinMessageBox( HWND_DESKTOP,
                             hwnd,
                             aboutmsg,
                             PROGNAME,
                             0, /* ID does not matter */
                             MB_OK         | MB_ICONEXCLAMATION |
                             MB_DEFBUTTON1 | MB_MOVEABLE      );
          return ((MRESULT)0);

        }

    default:
      return( (MRESULT)WinDefDlgProc( hwnd, msg, mp1, mp2 ) );
    }
}

/*==============================================================*/
/* This function brings up the selection dialog and returns     */
/* the selected entry or UK_CANCEL, if no selection was made    */
/* made by the user.                                            */
/*                                                              */
/* Parameter:                                                   */
/*   myhandle = window-handle of the calling window             */
/*              (only used as owner-window for the              */
/*               dialog-window; parent is the desktop)          */
/* Return:                                                      */
/*   selected index or UK_CANCEL                                */
/*==============================================================*/

int seldialog( HWND myhandle )
{
  LONG swapindex;
  swapindex = WinDlgBox( HWND_DESKTOP, myhandle , /* cast from ULONG to LONG */
                        ukseldlg, (HMODULE)NULL,
                        UK_SEL_DLG, (PVOID)&swapindex );
  switch ( swapindex )
    {
    case UK_CANCEL:
      return( UK_CANCEL );
    case UK_REINIT:
      return( UK_REINIT );
    default:
      return( (int)swapindex );
    }
}

/*==============================================================*/
/* Window-procedure for the windows of class szAreaClientClass. */
/*                                                              */
/* Beside the standard messages handled (CREATE,PAINT,SHOW; not */
/* DESTROY,QUIT as no resources are allocated by this class),   */
/* this procedure handles the private commands WMP_OPENSEL.     */
/*==============================================================*/

static MRESULT EXPENTRY AreaClientWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  static char   cmd[1000] = "";
  HPS    hps, hps_unused;
  RECTL  rcl;
  int    index;
  
  switch (msg)
    {
    case WM_CREATE:
      (void)WinDefWindowProc( hwnd, msg, mp1, mp2 );
      (void)WinPostMsg( hwnd, WMP_INITSEL, (MPARAM)0, (MPARAM)0 );
      return( (MRESULT)FALSE );

    case WM_PAINT:
      /* clear window by painting it in BACK_COLOR */
      hps_unused = WinBeginPaint (hwnd, 0L, 0L); /* tell PM we will draw */
      hps = WinGetPS( hwnd ); /* get presentation space for whole client area */
      (void)WinQueryWindowRect (hwnd, &rcl); /* and query the rectangle
                                              * coordinates
                                              */
      (void)WinFillRect(hps, &rcl, SYSCLR_BACKGROUND);
      (void)WinEndPaint (hps);  /* flag end of update, so that this client
                                 * window will be marked ok by PM
                                 */
      return (0);

    case WMP_INITSEL:
      if (fillSelTable( hwnd ) == UK_OK)
          (void)WinPostMsg( hwnd, WMP_OPENSEL, (MPARAM)0, (MPARAM)0 );
      else
          (void)WinSendMsg (hwnd, WM_CLOSE, 0L, 0L);
      return (0);

    case WMP_OPENSEL:
      if ((index = seldialog( hwnd )) == UK_CANCEL)
        {
          (void)WinSendMsg (hwnd, WM_CLOSE, 0L, 0L);
          return (0);
        }
      if ( index == UK_REINIT )
        {
          (void)WinSendMsg (hwnd, WMP_INITSEL, 0L, 0L);
          return (0);
        }
      /*
       * a selection was made
       */
      /* build command to execute */
      (void)sprintf(cmd, "start /N view %s", _uk_sel_table[index].param);
      /* change to drive */
      if ( _chdrive(_uk_sel_table[index].drive) < 0 )
        {
          cmd[0] = (char)(_uk_sel_table[index].drive - 1 + 'A');
          cmd[1] = '\0';
          errmsgbox( hwnd, "Can not change drive to", cmd );
        }
      else
        {
          /* change to directory */
          if ( _chdir(_uk_sel_table[index].wdir) < 0 )
              errmsgbox( hwnd, "Can not change directory to", _uk_sel_table[index].wdir );
          else
              /* now execute command */
              (void)system(cmd);
        }
      (void)_chdrive(startupdrive);
      (void)_chdir("\\");
      /* reopen selection dialog */
      (void)WinPostMsg( hwnd, WMP_OPENSEL, (MPARAM)0, (MPARAM)0 );
      return (0);
    } /* switch (msg) */
  return (WinDefWindowProc (hwnd, msg, mp1, mp2));
}

/*====================================================================*/
/* Determine x- and y-position of area-window (and by this of dialog) */
/* Order is:                                                          */
/*   default-position                                                 */
/*   from environment-variable  x,y                                   */
/*   from arguments to program  x y                                   */
/*====================================================================*/
void getxypos(int argc, char *argv[], long *xpos, long *ypos) {
    char *env,*komma;

    *xpos = (long)DEF_XPOS;
    *ypos = (long)DEF_YPOS;

    if (  ( (env = getenv( POSENVVAR )) != (char *)NULL )
       && (strlen(env) >= 3)
       && ((komma = strchr(env,',')) != (char *)NULL)
       && (komma != env)
       && (isdigit(*env))
       && (isdigit(*(komma+1)))
       )
      {
        *xpos = (long)atoi(env);
        *ypos = (long)atoi(komma+1);
      }

    if (  (argc == 3)
       && (isdigit(*(argv[1])))
       && (isdigit(*(argv[2])))
       )
      {
        *xpos = (long)atoi(argv[1]);
        *ypos = (long)atoi(argv[2]);
      }

   return;
}

/*==============================================================*/
/* main                                                         */
/* - initialise PM and get HAB of application                   */
/* - create message queue for application                       */
/* - register the 3 client window classes                       */
/* - create the 3 windows                                       */
/* - fill the window words of the CtrlClientWindow              */
/* - resize and position the Ctlr- and the Paint-window         */
/* - get all messages for this application and dispatch it to   */
/*   the appropriate window until a WM_QUIT is received         */
/* - destroy all windows                                        */
/* - destroy the message queue                                  */
/* - release PM and exit                                        */
/*==============================================================*/

int main (int argc, char *argv[])
{
  ULONG    flFrameFlags;
  HAB      hab;
  HMQ      hmq;
  HWND     hwndAreaFrame;
  HWND     hwndAreaClient;
  QMSG     qmsg;
  long     xpos, ypos;

  startupdrive = _getdrive();
  initSelTable();  /* fill in area-window-proc */
  getxypos(argc, argv, &xpos, &ypos);
  
  hab = WinInitialize ((ULONG)0) ;               /* only 0 allowed */
  if (hab == NULLHANDLE)
    {
      return 2;
    }

  hmq = WinCreateMsgQueue (hab, 0L) ;      /* 0 == default queue size */
  if (hmq == NULLHANDLE)
      (void)WinTerminate (hab);
 

  
  (void)WinRegisterClass (hab, szAreaClientClass, AreaClientWndProc,
                          CS_SIZEREDRAW,
                          0L);            /* 0 window words storage reserved */
  
  flFrameFlags = FCF_TITLEBAR | FCF_ICON | FCF_TASKLIST;
  
  hwndAreaFrame = WinCreateStdWindow (
                                   HWND_DESKTOP,
                                   WS_VISIBLE | WS_CLIPCHILDREN,
                                   &flFrameFlags,
                                   szAreaClientClass,
                                   PROGNAME,
                                   0L,
                                   0,
                                   ID_FW_AREA,
                                   &hwndAreaClient) ;
  
  (void)WinSetWindowPos( hwndAreaFrame,
                        HWND_TOP,
                        xpos,ypos,        /* x,y-coord rel to parent */
                        300L,20L,         /* x,y-dimension */
                        SWP_SIZE | SWP_MOVE | SWP_ZORDER | SWP_SHOW | SWP_ACTIVATE );

  while (WinGetMsg (hab, &qmsg, 0L, 0, 0))
    (void)WinDispatchMsg (hab, &qmsg);
  
  freeSelTable();  /* fill in area-window-proc */
  (void)WinDestroyWindow (hwndAreaClient);
  (void)WinDestroyWindow (hwndAreaFrame);
  (void)WinDestroyMsgQueue (hmq);
  (void)WinTerminate (hab);
  return (0);
}

