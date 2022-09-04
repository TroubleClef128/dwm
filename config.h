/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad	    = 10;	/* vertical padding of bar */
static const int sidepad	    = 10;	/* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=13","OpenSansEmoji:size=10","LiterationMono NF:pixelsize=24:intialias=true:autohint=true"};
static const char dmenufont[]       = {"monospace:size=10"};

/* default dwm colorscheme
static const char col_bg[]       = "#222222";
static const char col_border[]       = "#444444";
static const char col_fg[]       = "#bbbbbb";
static const char col_fg2[]       = "#eeeeee";
static const char col_bg2[]        = "#005577";
*/

/*my custom colors*/
static const char col_bg[]       = "#1b0c30";
static const char col_border[]       = "#444444";
static const char col_fg[]       = "#8cd5fa";
static const char col_fg2[]       = "#fc53d8";
static const char col_bg2[]        = "#1b0c30";
static const char col_border2[]     = "#3337b0";

static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_fg,    col_bg,    col_border },
        [SchemeSel]  = { col_fg2,   col_bg2,   col_border2},

	//colors below are made for the arrows and blocks on the status bar
	[0]	     = { "#d88ff7", "#1b0c30", "#ff0000" },
	[1]	     = { "#083a1a", "#d88ff7", "#ff0000" },
	[2]	     = { "#f772dd", "#d88ff7", "#ff0000" },
	[3]	     = { "#083a1a", "#f772dd", "#ff0000" },
	[4]	     = { "#f760ae", "#f772dd", "#ff0000" },
	[5]	     = { "#083a1a", "#f760ae", "#ff0000" },
	[6]	     = { "#f52052", "#f760ae", "#ff0000" },
	[7]	     = { "#083a1a", "#f52052", "#ff0000" },
	[8]	     = { "#000000", "#ffff00", "#ff0000" },
	[9]	     = { "#ffffff", "#ff0000", "#ff0000" },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_bg2, "-sf", col_fg2, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefoxcmd[] = {"firefox", NULL};
static const char *flameshot[] = {"flameshot", "gui", NULL};
static const char *ranger[] = {"st", "ranger", NULL};
static const char *google[] = {"surf", "google.com", NULL};

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_w,	   spawn,	   {.v = firefoxcmd } },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   {.v = flameshot } },
	{ MODKEY|ShiftMask,		XK_f,	   spawn,	   {.v = ranger } },
	{ MODKEY|ShiftMask,		XK_g,	   spawn,	   {.v = google } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,			XK_r,	   setlayout,	   {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,		XK_r,	   setlayout,	   {.v = &layouts[4]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
