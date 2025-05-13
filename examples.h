/****************************************************************************
 * Copyright 2025 Thomas E. Dickey                                          *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                          *
 * Except as contained in this notice, the name(s) of the above copyright   *
 * holders shall not be used in advertising or otherwise to promote the     *
 * sale, use or other dealings in this Software without prior written       *
 * authorization.                                                           *
 ****************************************************************************/

#ifndef EXAMPLES_H_incl
#define EXAMPLES_H_incl

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#include <X11/Xatom.h>

#if defined(HAVE_LIB_NEXTAW)
#include <X11/neXtaw/AsciiText.h>
#include <X11/neXtaw/Box.h>
#include <X11/neXtaw/Command.h>
#include <X11/neXtaw/Dialog.h>
#include <X11/neXtaw/Form.h>
#include <X11/neXtaw/Label.h>
#include <X11/neXtaw/List.h>
#include <X11/neXtaw/MenuButton.h>
#include <X11/neXtaw/Paned.h>
#include <X11/neXtaw/Panner.h>
#include <X11/neXtaw/Repeater.h>
#include <X11/neXtaw/Scrollbar.h>
#include <X11/neXtaw/SimpleMenu.h>
#include <X11/neXtaw/SmeBSB.h>
#include <X11/neXtaw/SmeLine.h>
#include <X11/neXtaw/StripChart.h>
#include <X11/neXtaw/Toggle.h>
#include <X11/neXtaw/Viewport.h>
#elif defined(HAVE_LIB_XAW3D)
#include <X11/Xaw3d/AsciiText.h>
#include <X11/Xaw3d/Box.h>
#include <X11/Xaw3d/Command.h>
#include <X11/Xaw3d/Dialog.h>
#include <X11/Xaw3d/Form.h>
#include <X11/Xaw3d/Label.h>
#include <X11/Xaw3d/List.h>
#include <X11/Xaw3d/MenuButton.h>
#include <X11/Xaw3d/Paned.h>
#include <X11/Xaw3d/Panner.h>
#include <X11/Xaw3d/Repeater.h>
#include <X11/Xaw3d/Scrollbar.h>
#include <X11/Xaw3d/SimpleMenu.h>
#include <X11/Xaw3d/SmeBSB.h>
#include <X11/Xaw3d/SmeLine.h>
#include <X11/Xaw3d/StripChart.h>
#include <X11/Xaw3d/Toggle.h>
#include <X11/Xaw3d/Viewport.h>
#elif defined(HAVE_LIB_XAWPLUS)
#include <X11/XawPlus/AsciiText.h>
#include <X11/XawPlus/Box.h>
#include <X11/XawPlus/Command.h>
#include <X11/XawPlus/Dialog.h>
#include <X11/XawPlus/Form.h>
#include <X11/XawPlus/Label.h>
#include <X11/XawPlus/List.h>
#include <X11/XawPlus/MenuButton.h>
#include <X11/XawPlus/Paned.h>
#include <X11/XawPlus/Panner.h>
#include <X11/XawPlus/Repeater.h>
#include <X11/XawPlus/Scrollbar.h>
#include <X11/XawPlus/SimpleMenu.h>
#include <X11/XawPlus/SmeBSB.h>
#include <X11/XawPlus/SmeLine.h>
#include <X11/XawPlus/StripChart.h>
#include <X11/XawPlus/Toggle.h>
#include <X11/XawPlus/Viewport.h>
#else
#include <X11/Xaw/AsciiText.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Dialog.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/List.h>
#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Panner.h>
#include <X11/Xaw/Repeater.h>
#include <X11/Xaw/Scrollbar.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>
#include <X11/Xaw/StripChart.h>
#include <X11/Xaw/Toggle.h>
#include <X11/Xaw/Viewport.h>
#endif

#ifdef USE_X11R5
#include <X11/Xaw/Clock.h>
#include <X11/Xaw/Logo.h>
#endif

#include <X11/Xaw/Cardinals.h>

#define ACTIONS_ARGS \
	(Widget w, XEvent *event, String *params, Cardinal *num_params)

#define CALLBACK_ARGS \
	(Widget w, XtPointer client_data, XtPointer call_data)

#endif /* EXAMPLES_H_incl */
