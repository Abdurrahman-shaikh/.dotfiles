#include <X11/keysymdef.h>
#include <X11/XF86keysym.h>
/*See LICENSE file for copyright and license details. */
// THIS IS A CHANGE
/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim       = ";";       /* Character used for separating status */
static const char *fonts[]          = { "Hack:size=12", "Symbols Nerd Font:size=12" };
static const char dmenufont[]       = "size=12";
static const char col_gray3[]       = "#f1be9b"; 
static const char col_gray1[]       = "#020914";
static const char col_gray2[]       = "#a8856c";
static const char col_gray4[]       = "#f1be9b"; 
static const char col_cyan[]        = "#63576E";
static const char *logoutcmd[] = { "killall", "Xorg", NULL };


static const unsigned int baralpha = 140;
static const unsigned int borderalpha = 140;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4 },
};




static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
//static const char *tags[] = { "Deus", "Vertias", "Pax", "Amor", "Libertas", "Sapientia", };
static const char *tags[] = { "", "", "", "", "", "", };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
  { MODKEY|ControlMask,   XK_l,       spawn,          {.v = logoutcmd } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *prtscrcmd[] = { "flameshot", "gui", NULL};
static const char *brightness_down[] = { "../scripts/brightness_control.sh", "down", NULL };
static const char *brightness_up[] = { "../scripts/brightness_control.sh", "up", NULL };
static const char *brupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brdowncmd[] = { "brightnessctl", "set", "10%-", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key                          function        argument */
	{ MODKEY,                       XK_p,                        spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                   spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                        togglebar,      {0} },
	{ MODKEY,                       XK_j,                        focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                        focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                        incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                        setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,                        movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                        movestack,      {.i = -1 } },
	{ MODKEY,                       XK_z,                        zoom,           {0} },
	{ MODKEY,                       XK_Tab,                      view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                        killclient,     {0} },
	{ MODKEY,                       XK_t,                        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                    setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                    togglefloating, {0} },
	{ MODKEY,                       XK_0,                        view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                        tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                    focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                   tagmon,         {.i = +1 } },
  { MODKEY,                       XF86XK_MonBrightnessDown,    spawn,          {.v = brightness_down } },
  { MODKEY,                       XF86XK_MonBrightnessUp,      spawn,          {.v = brightness_up } },
  { MODKEY|ShiftMask,             XK_i,                        spawn,          {.v = brightness_down } },
  { MODKEY|ShiftMask,             XK_d,                        spawn,          {.v = brightness_up } }, 
  { 0,                            XF86XK_MonBrightnessUp,      spawn,          {.v = brupcmd} },
  { 0,                            XF86XK_MonBrightnessDown,    spawn,          {.v = brdowncmd} },
  { MODKEY|ShiftMask,             XK_q,                        quit,           {0} },
  { 0,			                      XK_Print,                    spawn,	         {.v = prtscrcmd } },

	TAGKEYS(                        XK_1,                        0)
	TAGKEYS(                        XK_2,                        1)
	TAGKEYS(                        XK_3,                        2)
	TAGKEYS(                        XK_4,                        3)
	TAGKEYS(                        XK_5,                        4)
	TAGKEYS(                        XK_6,                        5)
	TAGKEYS(                        XK_7,                        6)
	TAGKEYS(                        XK_8,                        7)
	TAGKEYS(                        XK_9,                        8)
    // Increase brightness
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


static const char *statuscmd[] = { "slstatus", NULL };

static const char *const autostart[] = {
    "statuscmd",
    /* other autostart commands */
    NULL /* terminate the array */
};