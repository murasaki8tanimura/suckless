/* See LICENSE file for copyright and license details. */ /* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code:size=15" };
static const char dmenufont[]       = "Fira Code:size=15";
static const char col_bg[]          = "#282a36";
static const char col_fg[]          = "#f8f8f2";
static const char col_purple[]      = "#bd93f9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bg, col_bg },
	[SchemeSel]  = { col_bg, col_purple,  col_purple },
};

/* tagging */

static const char *tags[] = {"", "", "", "", "", "", ""};
static const Rule rules[] = {

	/* class      instance    title       tags mask   switchtotag    isfloating   monitor */

	/* WORKSPACE */
	{ "st",         NULL,       NULL,       1 << 1,      1,            0,           -1 },
	{ "URxvt",      NULL,       NULL,       1 << 1,      1,            0,           -1 },
	{ "code-oss",   NULL,       NULL,       1 << 1,      1,            0,           -1 },

	/* INTERNET */
	{ "firefox",    NULL,       NULL,       1 << 2,      1,            0,           -1 },
	{ "Chromium",   NULL,       NULL,       1 << 2,      1,            0,           -1 },

	/*FILE MANAGER*/
	{ "Pcmanfm",    NULL,       NULL,       1 << 3,      1,            0,           -1 },
	
	/*FILES/PHOTOS TAP 4*/
	{ "Zathura",    NULL,       NULL,       1 << 4,      1,            0,           -1 },
	{ "Sxiv",       NULL,       NULL,       1 << 4,      1,            0,           -1 },
	{ "mpv",        NULL,       NULL,       1 << 4,      1,            0,           -1 },

	/*MUSIC TAP 3*/
	{ "vlc",        NULL,       NULL,       1 << 5,      1,       	   0,           -1 },
	/*ETC*/
	{ "discord",    NULL,       NULL,       1 << 6,      1,       	   0,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "|+|",      tatami },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_purple, "-sf", col_bg, NULL };
static const char *termcmd[]  		= { "st", NULL };
static const char *secondterm[]	 	= { "urxvt", NULL };
static const char *firefox[]  		= { "firefox", NULL };
static const char *chromium[]  		= { "chromium", NULL };
static const char *filemanager[]	= { "pcmanfm", NULL };
static const char *audacious[]		= { "audacious", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = secondterm} },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = firefox} },
	{ MODKEY,                       XK_w,      spawn,          {.v = chromium } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filemanager} },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = audacious} },
	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },
	{ MODKEY|ControlMask,           XK_q,	   quit,           {0}  },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,	   killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_1,                      0)
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

