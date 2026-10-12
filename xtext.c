/*
 * xtext.c
 *
 * This is an example of how to use the Text and Paned widgets.
 *
 * November 14, 1989 - Chris D. Peterson
 */

/*
 * $XTermId: xtext.c,v 1.5 2026/10/12 10:18:12 tom Exp $
 * Copyright 2026, Thomas E. Dickey
 *
 * $XConsortium: xtext.c,v 1.16 91/05/16 14:56:23 swick Exp $
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

static void ClearText CALLBACK_ARGS;
static void PrintText CALLBACK_ARGS;
static void Syntax(XtAppContext, const char *);

String fallback_resources[] = {
    "*input:				True",
    "*showGrip:				off",
    "?.?.text.preferredPaneSize:	200",
    "?.?.text.textSource.editType:	edit",
    "?.?.text.scrollVertical:		whenNeeded",
    "?.?.text.scrollHorizontal:		whenNeeded",
    "?.?.text.autoFill:			on",
    "*clear*label:            Click here to clear the text widget.",
    "*print*label:            Click here to print the text to `stdout'.",
    NULL,
};

int
main(int argc, char **argv)
{
    XtAppContext app_con;
    Widget toplevel, paned, clear, print, text;
    Arg args[1];
    const char *filename = NULL;

    toplevel = XtAppInitialize(&app_con, "Xtext", NULL, ZERO,
			       &argc, argv, fallback_resources,
			       NULL, ZERO);

    /*
     * Check to see that all arguments were processed, and if not then
     * report an error and exit.
     */

    if (argc > 2) {
	Syntax(app_con, argv[0]);
    } else if (argc == 2) {
	filename = argv[1];
    }

    paned = XtCreateManagedWidget("paned", panedWidgetClass, toplevel,
				  NULL, ZERO);

    clear = XtCreateManagedWidget("clear", commandWidgetClass, paned,
				  NULL, ZERO);

    print = XtCreateManagedWidget("print", commandWidgetClass, paned,
				  NULL, ZERO);

    if (filename != NULL) {
    } else {
	XtSetArg(args[0], XtNstring,
		 "This is a\n"
		 "test.  If this\n"
		 "had been an actual\nemergency...");
    }

    text = XtCreateManagedWidget("text", asciiTextWidgetClass, paned,
				 args, ONE);

    XtAddCallback(clear, XtNcallback, ClearText, (XtPointer) text);
    XtAddCallback(print, XtNcallback, PrintText, (XtPointer) text);

    XtRealizeWidget(toplevel);
    XtAppMainLoop(app_con);
}

/*	Function Name: ClearText
 *	Description: This function clears all text out of the text widget.
 *	Arguments: w - *** UNUSED ***
 *                 text_ptr - a pointer to the text widget.
 *                 call_data - *** UNUSED ***.
 *	Returns: none.
 */

/* ARGSUSED */
static void
ClearText(
	Widget w _X_UNUSED,
	XtPointer text_ptr,
	XtPointer call_data _X_UNUSED)
{
    Widget text = (Widget) text_ptr;
    Arg args[1];

    XtSetArg(args[0], XtNstring, "");
    XtSetValues(text, args, ONE);
}

/*	Function Name: PrintText
 *	Description: This function clears all text out of the text widget.
 *	Arguments: w - *** UNUSED ***
 *                 text_ptr - a pointer to the text widget.
 *                 call_data - *** UNUSED ***.
 *	Returns: none.
 */

/* ARGSUSED */
static void
PrintText(
	Widget w _X_UNUSED,
	XtPointer text_ptr,
	XtPointer call_data _X_UNUSED)
{
    Widget text = (Widget) text_ptr;
    Arg args[1];
    String str;

    XtSetArg(args[0], XtNstring, &str);
    XtGetValues(text, args, ONE);

    fprintf(stdout, "Text String is:\n--------\n%s\n--------\n", str);
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
    fprintf( stderr, "Usage: %s [filename]\n", call);
    exit(1);
}

