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
