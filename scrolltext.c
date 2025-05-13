/*
 * Example from bug report.
 */
#include "examples.h"

static void	quit CALLBACK_ARGS;
static void	print CALLBACK_ARGS;

int
main(int argc, char *argv[])
{
	Cardinal	n;
	char		*string = "this text is too long to fit into the box";
	Widget		toplevel;
	Widget		box;
	Widget		command;
	Widget		print_widget;
	Widget		text_widget;
	Arg		wargs[12];

	toplevel = XtInitialize(argv[0], "Scrolltext", NULL, 0, &argc, argv);

	box = XtCreateManagedWidget("box", boxWidgetClass, toplevel, NULL, 0);

	n = 0;
	XtSetArg(wargs[n],XtNorientation,XtorientVertical); ++n;
	XtSetArg(wargs[n],XtNvSpace,10); ++n;
	XtSetValues(box, wargs, n);

	command = XtCreateManagedWidget("quit",
			commandWidgetClass, box, NULL, 0);
	XtAddCallback(command, XtNcallback, quit, NULL);

	print_widget = XtCreateWidget("print", commandWidgetClass, box,
			NULL, 0);

	n = 0;
	XtSetArg(wargs[n], XtNorientation, XtorientVertical); ++n;
	XtSetArg(wargs[n], XtNvSpace, 20); ++n;
	XtSetArg(wargs[n], XtNeditType, XawtextEdit); ++n;
	XtSetArg(wargs[n], XtNstring, string); ++n;
	XtSetArg(wargs[n], XtNsensitive, True); ++n;
	XtSetArg(wargs[n], XtNwidth, 80); ++n;
	XtSetArg(wargs[n], XtNheight, 40); ++n;
	XtSetArg(wargs[n], XtNscrollHorizontal, XawtextScrollWhenNeeded); ++n;

	text_widget = XtCreateWidget("text", asciiTextWidgetClass, box,
			wargs, n);

	XtAddCallback(print_widget, XtNcallback, print, text_widget);

	XtManageChild(print_widget);
	XtManageChild(text_widget);

	XtRealizeWidget(toplevel);

	XtMainLoop();
}


static void
quit(Widget w, XtPointer client, XtPointer call)
{
	(void)w; (void)client; (void)call;
	exit(EXIT_SUCCESS);
}


static void
print(Widget w _X_UNUSED, XtPointer client, XtPointer call _X_UNUSED)
{
	Arg	warg[1];
	char	*string;

	XtSetArg(warg[0], XtNstring, &string);
	XtGetValues((Widget)client, warg, 1);
	puts(string);
}
