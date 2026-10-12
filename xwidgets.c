/*
 * This example uses all the Athena widgets, and demonstrates timeouts.
 *
 * November 30, 1989 - Chris D. Peterson
 */

/*
 * $XTermId: xwidgets.c,v 1.7 2026/10/12 10:18:12 tom Exp $
 * Copyright 2026, Thomas E. Dickey
 *
 * $XConsortium: xwidgets.c,v 1.29 91/01/22 20:02:39 gildea Exp $
 *
 * Copyright 1989 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * M.I.T. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL M.I.T.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <examples.h>

String fallback_resources[] = {
    "*input:                  True",
    "*Paned.width:            350",
    "*label.label:            At least one of each Athena Widget.",
    "*Dialog.label:           I am a Dialog widget.",
    "*Dialog.value:           Enter new value here.",
    "*Dialog*command*label:   ok",
    "*Dialog*resizable:       True",
    "*Viewport*allowVert:     True",
    "*Form*formLabel.label:   0",
    "*Form*resizable:       True",
    "*StripChart*update:      1",
    "*StripChart*jumpScroll:  1",
    "*Box*allowResize:        True",
    "*scrollbar*orientation:  horizontal",
    "*scrollbar*length:       100",
    "*text*height:            75",
    "*text*string:            Look ma,\\na text widget!",
    "*text*editType:          edit",
    "*text*scrollVertical:    whenNeeded",
    "*text*scrollHorizonal:   whenNeeded",
    "*textFile*type:          file",
    "*textFile*string:        /etc/motd",
    "*textFile*scrollVertical:    whenNeeded",
    "*textFile*scrollHorizonal:   whenNeeded",
    "*textFile*height:        75",
    NULL,
};

static void Destroyed CALLBACK_ARGS;
static void Quit CALLBACK_ARGS;
static void Count CALLBACK_ARGS;
static void Syntax(XtAppContext, const char *);
static void CreateFormWithButtons(Widget);
static void CreateBox(Widget);
static void Okay CALLBACK_ARGS;
static void Scrolled CALLBACK_ARGS;
static void Thumbed CALLBACK_ARGS;
static void Finish(XtPointer, XtIntervalId *);
static void TimeSinceTouched CALLBACK_ARGS;

int
main(int argc, char **argv)
{
    Widget toplevel, outer, dialog, quit, chart, list, viewport;
    XtAppContext app_con;

#ifdef USE_X11R5
    Widget box;
#endif

    toplevel = XtAppInitialize(&app_con, "Xwidgets", NULL, ZERO,
			       &argc, argv, fallback_resources,
			       NULL, ZERO);

    if (argc != 1)
	Syntax(app_con, argv[0]);

    XtAddCallback( toplevel, XtNdestroyCallback, Destroyed, NULL );

    outer = XtCreateManagedWidget( "paned", panedWidgetClass, toplevel,
				  NULL, ZERO);

    quit = XtCreateManagedWidget( "quit", commandWidgetClass, outer,
				 NULL, ZERO);
    XtAddCallback( quit, XtNcallback, Quit, (XtPointer) toplevel);

    (void)XtCreateManagedWidget( "label", labelWidgetClass, outer, NULL, ZERO);

    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, outer,
				   NULL, ZERO);

    viewport = XtCreateManagedWidget( "viewport", viewportWidgetClass, outer,
				     NULL, ZERO);

    list = XtCreateManagedWidget("list", listWidgetClass, viewport,
				 NULL, ZERO);

    XawDialogAddButton(dialog, "command", Okay, (XtPointer) list);


    CreateFormWithButtons(outer);

#ifdef USE_X11R5
    box = XtCreateManagedWidget( "box", boxWidgetClass, outer, NULL, ZERO);
    (void) XtCreateManagedWidget(NULL, clockWidgetClass, box, NULL, ZERO);
    (void) XtCreateManagedWidget(NULL, logoWidgetClass, box, NULL, ZERO);
#endif

    chart = XtCreateManagedWidget("stripChart", stripChartWidgetClass, outer,
				  NULL, ZERO);
    XtAddCallback(chart, XtNgetValue, TimeSinceTouched, NULL);

    (void) XtCreateManagedWidget("text", asciiTextWidgetClass,outer,NULL,ZERO);

    CreateBox(outer);

    (void) XtCreateManagedWidget("textFile", asciiTextWidgetClass, outer,
				 NULL, ZERO);

    XtRealizeWidget(toplevel);
    XtAppMainLoop(app_con);
}

/*	Function Name: CreateFormWithButtons
 *	Description: Creates a form widget that contains:
 *                   a label, command, toggle, and menu button.
 *	Arguments: parent - the parent of the form widget.
 *	Returns: none.
 */

static void
CreateFormWithButtons(Widget parent)
{
    Widget form, label, button, menu;
    int i;
    Arg args[1];

    form = XtCreateManagedWidget( "form", formWidgetClass, parent,
				 NULL, ZERO );

    label = XtCreateManagedWidget("formLabel",labelWidgetClass,form,NULL,ZERO);

    XtSetArg(args[0], XtNfromHoriz, label);
    button = XtCreateManagedWidget("command",commandWidgetClass,form,args,ONE);
    XtAddCallback( button, XtNcallback, Count, (XtPointer) label );

    XtSetArg(args[0], XtNfromHoriz, button);
    button = XtCreateManagedWidget("toggle", toggleWidgetClass, form,args,ONE);
    XtAddCallback( button, XtNcallback, Count, (XtPointer) label );

    XtSetArg(args[0], XtNfromHoriz, button);
    button = XtCreateManagedWidget("menuButton", menuButtonWidgetClass, form,
				   args, ONE);

    menu = XtCreatePopupShell("menu", simpleMenuWidgetClass, button,NULL,ZERO);

    for (i = 0; i < 5; i++) {
	char buf[BUFSIZ];
	sprintf(buf, "menuEntry%d", i + 1);
	(void) XtCreateManagedWidget(buf, smeBSBObjectClass, menu,
				     NULL, ZERO);
	if (i == 2)
	    (void) XtCreateManagedWidget("menuButton", smeLineObjectClass,
					 menu, NULL, ZERO);
    }
}

/*	Function Name: CreateBox
 *	Description: Creates a box with a label and a scrollbar in it.
 *	Arguments: parent - the parent of the box.
 *	Returns: none.
 */

static void
CreateBox(Widget parent)
{
    Widget box, scrollbar, label;

    box = XtCreateManagedWidget(NULL, boxWidgetClass, parent, NULL, ZERO);

    scrollbar = XtCreateManagedWidget("scrollbar", scrollbarWidgetClass, box,
				      NULL, ZERO);

    label = XtCreateManagedWidget("scroll_label", labelWidgetClass, box,
				  NULL, ZERO);

    XtAddCallback(scrollbar, XtNjumpProc, Thumbed, (XtPointer) label);
    XtAddCallback(scrollbar, XtNscrollProc, Scrolled, (XtPointer) label);
}

/*	Function Name: Syntax
 *	Description: Prints a the calling syntax for this function to stdout.
 *	Arguments: app_con - the application context.
 *                 call - the name of the application.
 *	Returns: none - exits tho.
 */

static void
Syntax(XtAppContext app_con, const char *call)
{
    XtDestroyApplicationContext(app_con);
    fprintf(stderr, "Usage: %s\n", call);
    exit(1);
}

/*	Function Name: TimeSinceTouched
 *	Description: This function returns the number of 10s of seconds since
 *                   the user caused an event in this application.
 *	Arguments: widget - the strip chart widget.
 *                 closure - unused.
 *                 value_ptr - a pointer to the value to return.
 *	Returns: none
 */

/* ARGSUSED */
static void
TimeSinceTouched(
	Widget widget,
	XtPointer closure _X_UNUSED,
	XtPointer value_ptr)
{
    double *value = (double *) value_ptr;
    static double old_value = 0.0;
    static Time old_stamp = 1;
    Time new_stamp;

    new_stamp = XtLastTimestampProcessed(XtDisplay(widget));

    if (old_stamp != new_stamp) {
	old_stamp = new_stamp;
	old_value = 0.0;
    }
    else {
	Arg args[1];
	int update;

	XtSetArg(args[0], XtNupdate, &update);
	XtGetValues(widget, args, ONE);
	old_value += (double) update / 10.0;
    }

    *value = old_value;

}

/*	Function Name: Quit
 *	Description: Destroys all widgets, and returns.
 *	Arguments: widget - the widget that called this callback.
 *                 closure, callData - *** UNUSED ***.
 *	Returns: none
 *
 * NOTE:  The shell widget has a destroy callback that sets a five second
 *        timer, and at the end of that time the program exits.
 */

/* ARGSUSED */
static void
Quit(
	Widget widget _X_UNUSED,
	XtPointer closure,
	XtPointer callData _X_UNUSED)
{
    fprintf(stderr, "command callback.\n");
    XtDestroyWidget((Widget)closure);
}

/*	Function Name: Count
 *	Description: This callback routin will increment that counter
 *                   and display the number as the label of the widget passed
 *                   in the closure.
 *	Arguments: widget - *** UNUSED ***
 *                 closure - a pointer to the label widge to display the
 *                           string in.
 *                 callData - *** UNUSED ***
 *	Returns: none
 */

/* ARGSUSED */
static void
Count(
	Widget widget _X_UNUSED,
	XtPointer closure,
	XtPointer callData _X_UNUSED)
{
   Arg arg[1];
   char text[20];
   static int count = 0;

   sprintf( text, " %d ", ++count );
   XtSetArg( arg[0], XtNlabel, text );
   XtSetValues( (Widget)closure, arg, ONE );
}

/*	Function Name: Okay
 *	Description: Adds an entry to the List widget passed as clientData.
 *                   The name of this entry is the value of the dialog widget.
 *	Arguments: widget - the button that called this callback.
 *                 clientData - the list widget to add the entry to.
 *                 callData - *** UNUSED ***.
 *	Returns: none.
 *
 * NOTE: It is assumed that the button is a child of the dialog.
 */

/* ARGSUSED */
static void
Okay(
	Widget widget,
	XtPointer clientData,
	XtPointer callData _X_UNUSED)
{
    Widget list_widget = (Widget) clientData;
    static char **list = NULL;
    static int num_items = 0, allocated_items = 0;

    if (num_items == allocated_items) {
	allocated_items += 10;
	list = (char **) XtRealloc((char *)list,
				    (Cardinal) sizeof(String) *
				    (Cardinal) allocated_items);
    }

    /*
     * The value returned by XawDialogGetValueString() does not remain good
     * forever so we must store is somewhere.  This creates a memory leak
     * since I don't remember these values, and free them later.  I know about
     * it, but it doesn't seem worth fixing in this example.
     */

    list[num_items++] = XtNewString(XawDialogGetValueString(XtParent(widget)));
    XawListChange(list_widget, (const char **) list, num_items, 0, True);
}

/*	Function Name: Scrolled.
 *	Description: Prints the location of the pointer into the label
 *                   widget provided.
 *	Arguments: widget - *** UNUSED ***.
 *                 label_ptr - a pointer to the label widget.
 *                 value_ptr - the amount the bar has been scrolled.
 *	Returns: none
 */

/* ARGSUSED */
static void
Scrolled(
	Widget widget _X_UNUSED,
	XtPointer label_ptr,
	XtPointer value_ptr)
{
    int value = (int) (intptr_t) value_ptr;
    Widget label = (Widget) label_ptr;
    Arg args[1];
    char message[BUFSIZ];

    sprintf( message, " Scrolled by %d pixels", value);
    XtSetArg( args[0], XtNlabel, message );
    XtSetValues( label, args, ONE );
}

/*	Function Name: Thumbed.
 *	Description: Prints the location of the thumb as a percentage of the
 *                   height of the scrollbar into the label widget provided.
 *	Arguments: widget - *** UNUSED ***.
 *                 label_ptr - a pointer to the label widget.
 *                 top_ptr - a pointer to a float containing the location of
 *                           of the scrollbar's thumb.
 *	Returns:
 */

/* ARGSUSED */
static void
Thumbed(
	Widget widget _X_UNUSED,
	XtPointer label_ptr,
	XtPointer top_ptr)
{
    float top = *((float *) top_ptr);
    Widget label = (Widget) label_ptr;
    Arg args[1];
    char message[BUFSIZ];

    sprintf( message, " Thumbed to %d%% ", (int)(top*100) );
    XtSetArg( args[0], XtNlabel, message );
    XtSetValues( label, args, ONE );
}

/*	Function Name: Finish
 *	Description: This is a timeout function that will exit the program.
 *	Arguments: client_data, id - *** UNUSED ***.
 *	Returns: exits.
 */

/* ARGSUSED */
static void
Finish(XtPointer client_data _X_UNUSED, XtIntervalId *id _X_UNUSED)
{
    /*
     * I should really destroy the app_context here, but I am lazy, and
     * getting the app_context is a pain.
     */
    fprintf(stderr, "Bye!\n");
    exit(0);
}

/*	Function Name: Destroyed
 *	Description: This is a Destroy callback that when called sets a
 *                   timeout function that will exit the program in 5 seconds.
 *	Arguments: widget - the widget that was just destroyed.
 *                 closure, callData - UNUSED.
 *	Returns: none.
 */

/* ARGSUSED */
static void
	Destroyed(
	Widget widget,
	XtPointer closure _X_UNUSED,
	XtPointer callData _X_UNUSED)
{
    fprintf( stderr, "Everything now destroyed; setting 5 second timer.\n" );
    XtAppAddTimeOut(XtWidgetToApplicationContext(widget), 5000, Finish, NULL);
}
