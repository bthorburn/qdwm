/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

static const char col_label_00[] = "#eceff4"; /* White          */
static const char col_label_01[] = "#bf616a"; /* Red            */
static const char col_label_02[] = "#d08770"; /* Orange         */
static const char col_label_03[] = "#ebcb8b"; /* Yellow         */
static const char col_label_04[] = "#a3be8c"; /* Green          */
static const char col_label_05[] = "#bebebe"; /* Grey           */
static const char col_label_06[] = "#4363d8"; /* Blue           */
static const char col_label_07[] = "#b48ead"; /* Purple         */
static const char col_label_08[] = "#4c566a"; /* Black          */
static const char col_label_09[] = "#232323"; /* SchemeNorm     */
static const char col_label_10[] = "#222222"; /* SchemeStatus   */     
static const char col_label_11[] = "#2e3440"; /* SchemeTagsNorm */
static const char col_label_12[] = "#3b4252"; /* SchemeTagsSel  */
static const char col_label_13[] = "#434c5e"; /* SchemeInfoNorm */
static const char col_label_14[] = "#434c5e"; /* SchemeInfoSel  */
static const char col_label_15[] = "#d8dee9"; /* TextNorm       */
static const char col_label_16[] = "#e5e9f0"; /* TextSel        */


static const char *colors[][3]      = {	
  /* { fg, bg, border } */
  { col_label_09, col_label_00, col_label_00 }, /* [0] SchemeSel dom0      */
  { col_label_16, col_label_01, col_label_01 }, /* [1] SchemeSel label 1   */
  { col_label_16, col_label_02, col_label_02 }, /* [2] SchemeSel label 2   */
  { col_label_16, col_label_03, col_label_03 }, /* [3] SchemeSel label 3   */
  { col_label_16, col_label_04, col_label_04 }, /* [4] SchemeSel label 4   */
  { col_label_16, col_label_05, col_label_05 }, /* [5] SchemeSel label 5   */
  { col_label_16, col_label_06, col_label_06 }, /* [6] SchemeSel label 6   */
  { col_label_16, col_label_07, col_label_07 }, /* [7] SchemeSel label 7   */ 
  { col_label_16, col_label_08, col_label_08 }, /* [8] SchemeSel label 8   */
  { col_label_15, col_label_09, col_label_09 }, /* [9] SchemeNorm          */
  { col_label_15, col_label_10, "#000000"    }, /* [10] SchemeStatus       */ 
  { col_label_15, col_label_11, "#000000"    }, /* [11] SchemeTagsNorm     */
  { col_label_16, col_label_12, "#000000"    }, /* [12] SchemeTagsSel      */
  { col_label_15, col_label_13, "#000000"    }, /* [13] SchemeInfoNorm     */
  { col_label_16, col_label_14, "#000000"    }, /* [14] SchemeInfoSel      */
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	_QUBES_LABEL(CARDINAL) = label
	 *	_QUBES_VMNAME(STRING) = qube
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* label  qube        class      instance    title       tags mask     isfloating   monitor */
	 { 0,    "personal", "Gimp",     NULL,       NULL,       0,            1,           -1 },
	 { 6,     NULL,      "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = {
  "dmenu_run",
  "-m",
  dmenumon,
  "-fn",
  dmenufont,
  "-nb",
  col_label_16,
  "-nf",
  col_label_09,
  "-sb",
  col_label_10,
  "-sf",
  col_label_02,
  NULL
};

static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
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
static const Button buttons[] = {
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
