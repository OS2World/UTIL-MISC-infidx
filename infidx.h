/*===========================================================================
 * infidx.h  -- for documentation see infidx.c
 *
 * $Log:	infidx.h $
 *Revision 1.3  93/07/03  18:42:35  UWE
 *- seperated the program version number from the RCS revision
 *- added a licence and disclaimer to the documentation
 *
 *Revision 1.2  93/07/02  11:10:41  UWE
 *Added positioning possibility by user and REINIT-button.
 *
 *Revision 1.1  93/07/01  22:08:37  UWE
 *Initial revision
 *
 * 
 *===========================================================================*/

/********************/
/* Normal C-defines */
/********************/
#define UKVERSION      "1.3"
#define PROGNAME       "INFIDX - *.INF-index/starter"
#define ENVVARNAME     "BOOKSHELF"
#define POSENVVAR      "INFIDX"
#define DEF_XPOS       0
#define DEF_YPOS       0
#define CONFNAME       "infidx"
#define UK_RET         int
#define UK_OK          0
#define UK_ERR         1
#define UK_MAX_ENTRIES 300

/****************************************************************/
/* constants for the windows, menu-bars and the pull-down-menus */
/* (we only got one window without decoration)                  */
/****************************************************************/

/* the ID's of the menu-bars of the text-windows  */

#define ID_FW_AREA      1

/*********************************************************/
/* private message-id:                                   */
/* 1st will init  the selection dialog                   */
/* 2nd will start the selection dialog                   */
/*********************************************************/

#define WMP_INITSEL        (WM_USER + 1)
#define WMP_OPENSEL        (WM_USER + 2)

/*******************************************/
/* constants for the ID's of the elements  */
/* of the selection dialog box             */
/*******************************************/

#define UK_SEL_DLG                  100
#define UK_SEL_LBOX                 101
#define UK_SEL_ICON                 102
#define UK_SEL_OPEN                 103
#define UK_SEL_CANCEL               104
#define UK_SEL_REINIT               105
#define UK_SEL_ABOUT                106

/**************************************************************/
/* the values returned by the selection dialog window         */
/* procedure, if cancel or reinit was clicked;                */
/**************************************************************/

#define UK_CANCEL   (UK_MAX_ENTRIES + 10)
#define UK_REINIT   (UK_MAX_ENTRIES + 11)

