/*
   File:          AllColor.h
   Author:        Lakshminarayanan Venkatasubramanian
   		  J.K. Johnstone
   Created:       8 April 1998
   Last modified: 19 June 2003
   Purpose:       Color vectors.
   History: 	  From http://www.users.interport.net/~giant/COLOR/1ColorSpecifier.html
   		  7/10/02: Added material, pulled from glut-3.6/progs/redbook/teapots.c
		  6/19/03: Cleaned up.
   Dependence:    Independent of all libraries.
   Status:        Usable by my graphics PhD students.
*/

#ifndef _ALLCOLOR_
#define _ALLCOLOR_

float bronzeambient[3]   = {.33, .22, .27}; // Inventor Mentor,p. 50
float bronzediffuse[3]   = {.78, .57, .11};
float bronzespecular[3]  = {.99, .94, .81};
float bronzeshininess[1] = {.28};
float silverambient[3]   = {.2,  .2,  .2};
float silverdiffuse[3]   = {.6,  .6,  .6};
float silverspecular[3]  = {.5,  .5,  .5};
float silvershininess[1] = {.5};
material = ambient (4 floats), diffuse (4), specular (4), shininess (1)
float redplastic[13]     = {0.8,0.1,0.1,1, .8,.1,.1,1, 0.2,0.2,0.2,1, 5.0};
float emerald[13] = {0.0215,0.1745,0.0215,1, 0.07568,0.61424,0.07568,1, 0.633,0.727811,0.633,1, 0.6};
float jade[13]	  = {0.135,0.2225,0.1575,1,  0.54,0.89,0.63,1, 0.316228,0.316228,0.316228,1, 0.1};
float obsidian[13]= {0.05375,0.05,0.06625,1, 0.18275,0.17,0.22525,1, 0.332741,0.328634,0.346435,1, 0.3};
float pearl[13]   = {0.25,0.20725,0.20725,1, 1,0.829,0.829,1, 0.296648,0.296648,0.296648,1, 0.088};
float ruby[13]    = {0.1745,0.01175,0.01175,1, 0.61424,0.04136,0.04136,1, 0.727811,0.626959,0.626959,1, 0.6};
float turquoise[13] = {0.1,0.18725,0.1745,1, 0.396,0.74151,0.69102,1, 0.297254,0.30829,0.306678,1, 0.1};
float brass[13]={.329412,.223529,.027451,1, .780392,.568627,.113725,1, .992157,.941176,.807843,1, .21794872};
float bronze[13] = {0.2125,0.1275,0.054,1, 0.714,0.4284,0.18144,1, 0.393548,0.271906,0.166721,1, 0.2};
float material[][13]= { 
{0.0215,0.1745,0.0215,1, 0.07568,0.61424,0.07568,1, 0.633,0.727811,0.633,1, 0.6},	// emerald, good
{.0,.0,.0,1, 1,.0,.0,1, .7,.6,.6,1, .25},				                // red 1
{.0,.0,.0,1, .0,.0,1,1, .6,.6,.7,1, .25},				                // blue
{0.05375,0.05,0.06625,1, 0.18275,0.17,0.22525,1, 0.332741,0.328634,0.346435,1, 0.3},	// obsidian
{.329412,.223529,.027451,1, .780392,.568627,.113725,1, .992157,.941176,.807843,1, .21794872}, // brass
{0.2125,0.1275,0.054,1, 0.714,0.4284,0.18144,1, 0.393548,0.271906,0.166721,1, 0.2}, 	// bronze
{0.25,0.25,0.25,1, 0.4,0.4,0.4,1, 0.774597,0.774597,0.774597,1, 0.6},			// chrome
{0.19125,0.0735,0.0225,1, 0.7038,0.27048,0.0828,1, 0.256777,0.137622,0.086014, 1, 0.1},	// copper
{0.24725,0.1995,0.0745,1, 0.75164,0.60648,0.22648,1, 0.628281,0.555802,0.366065,1, 0.4},// gold
{.19225,.19225,.19225,1, .50754,.50754,.50754,1, .508273,.508273,.508273,1, .4},        // silver
{.0,.0,.0,1, 0.01,0.01,0.01,1, 0.50,0.50,0.50,1, .25},					// black
{.0,.1,.06,1, .0,.50980392,.50980392,1, .50196078,.50196078,.50196078,1, .25},		// cyan
{.0,.0,.0,1, .5,.0,.0,1, .7,.6,.6,1, .25},						// red 1
{.0,.0,.0,1, .1,.35,.1,1, .45,.55,.45,1, .25},	                                        // green 1
{.0,.0,.0,1, .55,.55,.55,1, .70,.70,.70,1, .25},	                                // white 1
{.0,.0,.0,1, .5,.5,.0,1, .60,.60,.50,1, .25},		                                // yellow plastic
{.02,.02,.02,1, .01,.01,.01,1, .4,.4,.4,1, .078125},	                                // black
{.0,.05,.05,1, .4,.5,.5,1, .04,.7,.7,1, .078125},	                                // cyan
{.0,.05,.0,1, .4,.5,.4,1, .04,.7,.04,1, .078125},	                                // green 2
{.05,.0,.0,1, .5,.4,.4,1, .7,.04,.04,1, .078125},	                                // red 2
{.05,.05,.05,1, .5,.5,.5,1, .7,.7,.7,1, .078125},	                                // white 2
{.1,.18725,.1745,1, .396,.74151,.69102,1, .297254,.30829,.306678,1, .1},		// turquoise (no good)
{.1745,.01175,.01175,1, .61424,.04136,.04136,1, .727811,.626959,.626959,1, .6}, 	// ruby
{.135,.2225,.1575,1, .54,.89,.63,1, .316228,.316228,.316228,1, .1},			// jade
{.25,.20725,.20725,1, 1,.829,.829,1, .296648,.296648,.296648,1, .088},		        // pearl (no good)
{.05,.05,.0,1, .5,.5,.4,1, .7,.7,.04,1, .078125}	                                // yellow rubber
};
float	Snow[3]		=	{1, 0.980392, 0.980392};
float	GhostWhite[3]	=	{0.972549, 0.972549, 1};
float	WhiteSmoke[3]	=	{0.960784, 0.960784, 0.960784};
float	Gainsboro[3]	=	{0.862745, 0.862745, 0.862745};
float	FloralWhite[3]	=	{1, 0.980392, 0.941176};
float	OldLace[3]	=	{0.992157, 0.960784, 0.901961};
float	Linen[3]	=	{0.980392, 0.941176, 0.901961};
float	AntiqueWhite[3]	=	{0.980392, 0.921569, 0.843137};
float	PapayaWhip[3]	=	{1, 0.937255, 0.835294};
float	BlanchedAlmond[3]=	{1, 0.921569, 0.803922};
float	Bisque[3]	=	{1, 0.894118, 0.768627};
float	PeachPuff[3]	=	{1, 0.854902, 0.72549};
float	NavajoWhite[3]	=	{1, 0.870588, 0.678431};
float	Moccasin[3]	=	{1, 0.894118, 0.709804};
float	Cornsilk[3]	=	{1, 0.972549, 0.862745};
float	Ivory[3]	=	{1, 1, 0.941176};
float	LemonChiffon[3]	=	{1, 0.980392, 0.803922};
float	Seashell[3]	=	{1, 0.960784, 0.933333};
float	Honeydew[3]	=	{0.941176, 1, 0.941176};
float	MintCream[3]	=	{0.960784, 1, 0.980392};
float	Azure[3]	=	{0.941176, 1, 1};
float	AliceBlue[3]	=	{0.941176, 0.972549, 1};
float	lavender[3]	=	{0.901961, 0.901961, 0.980392};
float	LavenderBlush[3]=	{1, 0.941176, 0.960784};
float	MistyRose[3]	=	{1, 0.894118, 0.882353};
float	White[3]	=	{1, 1, 1};
float	Black[3]	=	{0, 0, 0};
float	DarkSlateGray[3]=	{0.184314, 0.309804, 0.309804};
float	DimGrey[3]	=	{0.411765, 0.411765, 0.411765};
float	SlateGrey[3]	=	{0.439216, 0.501961, 0.564706};
float	LightSlateGray[3]=	{0.466667, 0.533333, 0.6};
float	Grey[3]		=	{0.745098, 0.745098, 0.745098};
float	LightGray[3]	=	{0.827451, 0.827451, 0.827451};
float	MidnightBlue[3]	=	{0.0980392, 0.0980392, 0.439216};
float	NavyBlue[3]	=	{0, 0, 0.501961};
float	CornflowerBlue[3]=	{0.392157, 0.584314, 0.929412};
float	DarkSlateBlue[3]=	{0.282353, 0.239216, 0.545098};
float	SlateBlue[3]	=	{0.415686, 0.352941, 0.803922};
float	MediumSlateBlue[3]=	{0.482353, 0.407843, 0.933333};
float	LightSlateBlue[3]=	{0.517647, 0.439216, 1};
float	MediumBlue[3]	=	{0, 0, 0.803922};
float	RoyalBlue[3]	=	{0.254902, 0.411765, 0.882353};
float	Blue[3]		=	{0, 0, 1};
float	DodgerBlue[3]	=	{0.117647, 0.564706, 1};
float	DeepSkyBlue[3]	=	{0, 0.74902, 1};
float	SkyBlue[3]	=	{0.529412, 0.807843, 0.921569};
float	LightSkyBlue[3]	=	{0.529412, 0.807843, 0.980392};
float	SteelBlue[3]	=	{0.27451, 0.509804, 0.705882};
float	LightSteelBlue[3]=	{0.690196, 0.768627, 0.870588};
float	LightBlue[3]	=	{0.678431, 0.847059, 0.901961};
float	PowderBlue[3]	=	{0.690196, 0.878431, 0.901961};
float	PaleTurquoise[3]=	{0.686275, 0.933333, 0.933333};
float	DarkTurquoise[3]=	{0, 0.807843, 0.819608};
float	MediumTurquoise[3]=	{0.282353, 0.819608, 0.8};
float	Turquoise[3]	=	{0.25098, 0.878431, 0.815686};
float	Cyan[3]		=	{0, 1, 1};
float	LightCyan[3]	=	{0.878431, 1, 1};
float	CadetBlue[3]	=	{0.372549, 0.619608, 0.627451};
float	MediumAquamarine[3]=	{0.4, 0.803922, 0.666667};
float	Aquamarine[3]	=	{0.498039, 1, 0.831373};
float	DarkGreen[3]	=	{0, 0.392157, 0};
float	DarkOliveGreen[3]=	{0.333333, 0.419608, 0.184314};
float	DarkSeaGreen[3]	=	{0.560784, 0.737255, 0.560784};
float	SeaGreen[3]	=	{0.180392, 0.545098, 0.341176};
float	MediumSeaGreen[3]=	{0.235294, 0.701961, 0.443137};
float	LightSeaGreen[3]=	{0.12549, 0.698039, 0.666667};
float	PaleGreen[3]	=	{0.596078, 0.984314, 0.596078};
float	SpringGreen[3]	=	{0, 1, 0.498039};
float	LawnGreen[3]	=	{0.486275, 0.988235, 0};
float	Green[3]	=	{0, 1, 0};
float	Chartreuse[3]	=	{0.498039, 1, 0};
float	MedSpringGreen[3]=	{0, 0.980392, 0.603922};
float	GreenYellow[3]	=	{0.678431, 1, 0.184314};
float	LimeGreen[3]	=	{0.196078, 0.803922, 0.196078};
float	YellowGreen[3]	=	{0.603922, 0.803922, 0.196078};
float	ForestGreen[3]	=	{0.133333, 0.545098, 0.133333};
float	OliveDrab[3]	=	{0.419608, 0.556863, 0.137255};
float	DarkKhaki[3]	=	{0.741176, 0.717647, 0.419608};
float	PaleGoldenrod[3]=	{0.933333, 0.909804, 0.666667};
float	LtGoldenrodYello[3]=	{0.980392, 0.980392, 0.823529};
float	LightYellow[3]	=	{1, 1, 0.878431};
float	Yellow[3]	=	{1, 1, 0};
float	Gold[3]		=	{1, 0.843137, 0};
float	LightGoldenrod[3]=	{0.933333, 0.866667, 0.509804};
float	goldenrod[3]	=	{0.854902, 0.647059, 0.12549};
float	DarkGoldenrod[3]=	{0.721569, 0.52549, 0.0431373};
float	RosyBrown[3]	=	{0.737255, 0.560784, 0.560784};
float	IndianRed[3]	=	{0.803922, 0.360784, 0.360784};
float	SaddleBrown[3]	=	{0.545098, 0.270588, 0.0745098};
float	Sienna[3]	=	{0.627451, 0.321569, 0.176471};
float	Peru[3]		=	{0.803922, 0.521569, 0.247059};
float	Burlywood[3]	=	{0.870588, 0.721569, 0.529412};
float	Beige[3]	=	{0.960784, 0.960784, 0.862745};
float	Wheat[3]	=	{0.960784, 0.870588, 0.701961};
float	SandyBrown[3]	=	{0.956863, 0.643137, 0.376471};
float	Tan[3]		=	{0.823529, 0.705882, 0.54902};
float	Chocolate[3]	=	{0.823529, 0.411765, 0.117647};
float	Firebrick[3]	=	{0.698039, 0.133333, 0.133333};
float	Brown[3]	=	{0.647059, 0.164706, 0.164706};
float	DarkSalmon[3]	=	{0.913725, 0.588235, 0.478431};
float	Salmon[3]	=	{0.980392, 0.501961, 0.447059};
float	LightSalmon[3]	=	{1, 0.627451, 0.478431};
float	Orange[3]	=	{1, 0.647059, 0};
float	DarkOrange[3]	=	{1, 0.54902, 0};
float	Coral[3]	=	{1, 0.498039, 0.313725};
float	LightCoral[3]	=	{0.941176, 0.501961, 0.501961};
float	Tomato[3]	=	{1, 0.388235, 0.278431};
float	OrangeRed[3]	=	{1, 0.270588, 0};
float	Red[3]		=	{1, 0, 0};
float	HotPink[3]	=	{1, 0.411765, 0.705882};
float	DeepPink[3]	=	{1, 0.0784314, 0.576471};
float	Pink[3]		=	{1, 0.752941, 0.796078};
float	LightPink[3]	=	{1, 0.713725, 0.756863};
float	PaleVioletRed[3]=	{0.858824, 0.439216, 0.576471};
float	Maroon[3]	=	{0.690196, 0.188235, 0.376471};
float	MediumVioletRed[3]=	{0.780392, 0.0823529, 0.521569};
float	VioletRed[3]	=	{0.815686, 0.12549, 0.564706};
float	Magenta[3]	=	{1, 0, 1};
float	Violet[3]	=	{0.933333, 0.509804, 0.933333};
float	Plum[3]		=	{0.866667, 0.627451, 0.866667};
float	Orchid[3]	=	{0.854902, 0.439216, 0.839216};
float	MediumOrchid[3]	=	{0.729412, 0.333333, 0.827451};
float	DarkOrchid[3]	=	{0.6, 0.196078, 0.8};
float	DarkViolet[3]	=	{0.580392, 0, 0.827451};
float	BlueViolet[3]	=	{0.541176, 0.168627, 0.886275};
float	Purple[3]	=	{0.627451, 0.12549, 0.941176};
float	MediumPurple[3]	=	{0.576471, 0.439216, 0.858824};
float	Thistle[3]	=	{0.847059, 0.74902, 0.847059};
float	Snow1[3]	=	{1, 0.980392, 0.980392};
float	Snow2[3]	=	{0.933333, 0.913725, 0.913725};
float	Snow3[3]	=	{0.803922, 0.788235, 0.788235};
float	Snow4[3]	=	{0.545098, 0.537255, 0.537255};
float	Seashell1[3]	=	{1, 0.960784, 0.933333};
float	Seashell2[3]	=	{0.933333, 0.898039, 0.870588};
float	Seashell3[3]	=	{0.803922, 0.772549, 0.74902};
float	Seashell4[3]	=	{0.545098, 0.52549, 0.509804};
float	AntiqueWhite1[3]=	{1, 0.937255, 0.858824};
float	AntiqueWhite2[3]=	{0.933333, 0.87451, 0.8};
float	AntiqueWhite3[3]=	{0.803922, 0.752941, 0.690196};
float	AntiqueWhite4[3]=	{0.545098, 0.513725, 0.470588};
float   Bisque1[3]      =       {1, 0.894118, 0.768627};
float	Bisque2[3]	=	{0.933333, 0.835294, 0.717647};
float	Bisque3[3]	=	{0.803922, 0.717647, 0.619608};
float	Bisque4[3]	=	{0.545098, 0.490196, 0.419608};
float	PeachPuff1[3]	=	{1, 0.854902, 0.72549};
float	PeachPuff2[3]	=	{0.933333, 0.796078, 0.678431};
float	PeachPuff3[3]	=	{0.803922, 0.686275, 0.584314};
float	PeachPuff4[3]	=	{0.545098, 0.466667, 0.396078};
float	NavajoWhite1[3]	=	{1, 0.870588, 0.678431};
float	NavajoWhite2[3]	=	{0.933333, 0.811765, 0.631373};
float	NavajoWhite3[3]	=	{0.803922, 0.701961, 0.545098};
float	NavajoWhite4[3]	=	{0.545098, 0.47451, 0.368627};
float	LemonChiffon1[3]=	{1, 0.980392, 0.803922};
float	LemonChiffon2[3]=	{0.933333, 0.913725, 0.74902};
float	LemonChiffon3[3]=	{0.803922, 0.788235, 0.647059};
float	LemonChiffon4[3]=	{0.545098, 0.537255, 0.439216};
float	Cornsilk1[3]	=	{1, 0.972549, 0.862745};
float	Cornsilk2[3]	=	{0.933333, 0.909804, 0.803922};
float	Cornsilk3[3]	=	{0.803922, 0.784314, 0.694118};
float	Cornsilk4[3]	=	{0.545098, 0.533333, 0.470588};
float	Ivory1[3]	=	{1, 1, 0.941176};
float	Ivory2[3]	=	{0.933333, 0.933333, 0.878431};
float	Ivory3[3]	=	{0.803922, 0.803922, 0.756863};
float	Ivory4[3]	=	{0.545098, 0.545098, 0.513725};
float	Honeydew1[3]	=	{0.941176, 1, 0.941176};
float	Honeydew2[3]	=	{0.878431, 0.933333, 0.878431};
float	Honeydew3[3]	=	{0.756863, 0.803922, 0.756863};
float	Honeydew4[3]	=	{0.513725, 0.545098, 0.513725};
float	LavenderBlush1[3]=	{1, 0.941176, 0.960784};
float	LavenderBlush2[3]=	{0.933333, 0.878431, 0.898039};
float	LavenderBlush3[3]=	{0.803922, 0.756863, 0.772549};
float	LavenderBlush4[3]=	{0.545098, 0.513725, 0.52549};
float	MistyRose1[3]	=	{1, 0.894118, 0.882353};
float	MistyRose2[3]	=	{0.933333, 0.835294, 0.823529};
float	MistyRose3[3]	=	{0.803922, 0.717647, 0.709804};
float	MistyRose4[3]	=	{0.545098, 0.490196, 0.482353};
float	Azure1[3]	=	{0.941176, 1, 1};
float	Azure2[3]	=	{0.878431, 0.933333, 0.933333};
float	Azure3[3]	=	{0.756863, 0.803922, 0.803922};
float	Azure4[3]	=	{0.513725, 0.545098, 0.545098};
float	SlateBlue1[3]	=	{0.513725, 0.435294, 1};
float	SlateBlue2[3]	=	{0.478431, 0.403922, 0.933333};
float	SlateBlue3[3]	=	{0.411765, 0.34902, 0.803922};
float	SlateBlue4[3]	=	{0.278431, 0.235294, 0.545098};
float	RoyalBlue1[3]	=	{0.282353, 0.462745, 1};
float	RoyalBlue2[3]	=	{0.262745, 0.431373, 0.933333};
float	RoyalBlue3[3]	=	{0.227451, 0.372549, 0.803922};
float	RoyalBlue4[3]	=	{0.152941, 0.25098, 0.545098};
float	Blue1[3]	=	{0, 0, 1};
float	Blue2[3]	=	{0, 0, 0.933333};
float	Blue3[3]	=	{0, 0, 0.803922};
float	Blue4[3]	=	{0, 0, 0.545098};
float	DodgerBlue1[3]	=	{0.117647, 0.564706, 1};
float	DodgerBlue2[3]	=	{0.109804, 0.52549, 0.933333};
float	DodgerBlue3[3]	=	{0.0941176, 0.454902, 0.803922};
float	DodgerBlue4[3]	=	{0.0627451, 0.305882, 0.545098};
float	SteelBlue1[3]	=	{0.388235, 0.721569, 1};
float	SteelBlue2[3]	=	{0.360784, 0.67451, 0.933333};
float	SteelBlue3[3]	=	{0.309804, 0.580392, 0.803922};
float	SteelBlue4[3]	=	{0.211765, 0.392157, 0.545098};
float	DeepSkyBlue1[3]	=	{0, 0.74902, 1};
float	DeepSkyBlue2[3]	=	{0, 0.698039, 0.933333};
float	DeepSkyBlue3[3]	=	{0, 0.603922, 0.803922};
float	DeepSkyBlue4[3]	=	{0, 0.407843, 0.545098};
float	SkyBlue1[3]	=	{0.529412, 0.807843, 1};
float	SkyBlue2[3]	=	{0.494118, 0.752941, 0.933333};
float	SkyBlue3[3]	=	{0.423529, 0.65098, 0.803922};
float	SkyBlue4[3]	=	{0.290196, 0.439216, 0.545098};
float	LightSkyBlue1[3]=	{0.690196, 0.886275, 1};
float	LightSkyBlue2[3]=	{0.643137, 0.827451, 0.933333};
float	LightSkyBlue3[3]=	{0.552941, 0.713725, 0.803922};
float	LightSkyBlue4[3]=	{0.376471, 0.482353, 0.545098};
float	SlateGray1[3]	=	{0.776471, 0.886275, 1};
float	SlateGray2[3]	=	{0.72549, 0.827451, 0.933333};
float	SlateGray3[3]	=	{0.623529, 0.713725, 0.803922};
float	SlateGray4[3]	=	{0.423529, 0.482353, 0.545098};
float	LightSteelBlue1[3]=	{0.792157, 0.882353, 1};
float	LightSteelBlue2[3]=	{0.737255, 0.823529, 0.933333};
float	LightSteelBlue3[3]=	{0.635294, 0.709804, 0.803922};
float	LightSteelBlue4[3]=	{0.431373, 0.482353, 0.545098};
float	LightBlue1[3]	=	{0.74902, 0.937255, 1};
float	LightBlue2[3]	=	{0.698039, 0.87451, 0.933333};
float	LightBlue3[3]	=	{0.603922, 0.752941, 0.803922};
float	LightBlue4[3]	=	{0.407843, 0.513725, 0.545098};
float	LightCyan1[3]	=	{0.878431, 1, 1};
float	LightCyan2[3]	=	{0.819608, 0.933333, 0.933333};
float	LightCyan3[3]	=	{0.705882, 0.803922, 0.803922};
float	LightCyan4[3]	=	{0.478431, 0.545098, 0.545098};
float	PaleTurquoise1[3]=	{0.733333, 1, 1};
float	PaleTurquoise2[3]=	{0.682353, 0.933333, 0.933333};
float	PaleTurquoise3[3]=	{0.588235, 0.803922, 0.803922};
float	PaleTurquoise4[3]=	{0.4, 0.545098, 0.545098};
float	CadetBlue1[3]	=	{0.596078, 0.960784, 1};
float	CadetBlue2[3]	=	{0.556863, 0.898039, 0.933333};
float	CadetBlue3[3]	=	{0.478431, 0.772549, 0.803922};
float	CadetBlue4[3]	=	{0.32549, 0.52549, 0.545098};
float	Turquoise1[3]	=	{0, 0.960784, 1};
float	Turquoise2[3]	=	{0, 0.898039, 0.933333};
float	Turquoise3[3]	=	{0, 0.772549, 0.803922};
float	Turquoise4[3]	=	{0, 0.52549, 0.545098};
float	Cyan1[3]	=	{0, 1, 1};
float	Cyan2[3]	=	{0, 0.933333, 0.933333};
float	Cyan3[3]	=	{0, 0.803922, 0.803922};
float	Cyan4[3]	=	{0, 0.545098, 0.545098};
float	DarkSlateGray1[3]=	{0.592157, 1, 1};
float	DarkSlateGray2[3]=	{0.552941, 0.933333, 0.933333};
float	DarkSlateGray3[3]=	{0.47451, 0.803922, 0.803922};
float	DarkSlateGray4[3]=	{0.321569, 0.545098, 0.545098};
float	Aquamarine1[3]	=	{0.498039, 1, 0.831373};
float	Aquamarine2[3]	=	{0.462745, 0.933333, 0.776471};
float	Aquamarine3[3]	=	{0.4, 0.803922, 0.666667};
float	Aquamarine4[3]	=	{0.270588, 0.545098, 0.454902};
float	DarkSeaGreen1[3]=	{0.756863, 1, 0.756863};
float	DarkSeaGreen2[3]=	{0.705882, 0.933333, 0.705882};
float	DarkSeaGreen3[3]=	{0.607843, 0.803922, 0.607843};
float	DarkSeaGreen4[3]=	{0.411765, 0.545098, 0.411765};
float	SeaGreen1[3]	=	{0.329412, 1, 0.623529};
float	SeaGreen2[3]	=	{0.305882, 0.933333, 0.580392};
float	SeaGreen3[3]	=	{0.262745, 0.803922, 0.501961};
float	SeaGreen4[3]	=	{0.180392, 0.545098, 0.341176};
float	PaleGreen1[3]	=	{0.603922, 1, 0.603922};
float	PaleGreen2[3]	=	{0.564706, 0.933333, 0.564706};
float	PaleGreen3[3]	=	{0.486275, 0.803922, 0.486275};
float	PaleGreen4[3]	=	{0.329412, 0.545098, 0.329412};
float	SpringGreen1[3]	=	{0, 1, 0.498039};
float	SpringGreen2[3]	=	{0, 0.933333, 0.462745};
float	SpringGreen3[3]	=	{0, 0.803922, 0.4};
float	SpringGreen4[3]	=	{0, 0.545098, 0.270588};
float   Green1[3]       =       {0, 1, 0};
float	Green2[3]	=	{0, 0.933333, 0};
float	Green3[3]	=	{0, 0.803922, 0};
float	Green4[3]	=	{0, 0.545098, 0};
float	Chartreuse1[3]	=	{0.498039, 1, 0};
float	Chartreuse2[3]	=	{0.462745, 0.933333, 0};
float	Chartreuse3[3]	=	{0.4, 0.803922, 0};
float	Chartreuse4[3]	=	{0.270588, 0.545098, 0};
float	OliveDrab1[3]	=	{0.752941, 1, 0.243137};
float	OliveDrab2[3]	=	{0.701961, 0.933333, 0.227451};
float	OliveDrab3[3]	=	{0.603922, 0.803922, 0.196078};
float	OliveDrab4[3]	=	{0.411765, 0.545098, 0.133333};
float	DarkOliveGreen1[3]=	{0.792157, 1, 0.439216};
float	DarkOliveGreen2[3]=	{0.737255, 0.933333, 0.407843};
float	DarkOliveGreen3[3]=	{0.635294, 0.803922, 0.352941};
float	DarkOliveGreen4[3]=	{0.431373, 0.545098, 0.239216};
float	Khaki1[3]	=	{1, 0.964706, 0.560784};
float	Khaki2[3]	=	{0.933333, 0.901961, 0.521569};
float	Khaki3[3]	=	{0.803922, 0.776471, 0.45098};
float	Khaki4[3]	=	{0.545098, 0.52549, 0.305882};
float	LightGoldenrod1[3]=	{1, 0.92549, 0.545098};
float	LightGoldenrod2[3]=	{0.933333, 0.862745, 0.509804};
float	LightGoldenrod3[3]=	{0.803922, 0.745098, 0.439216};
float	LightGoldenrod4[3]=	{0.545098, 0.505882, 0.298039};
float	LightYellow1[3]	=	{1, 1, 0.878431};
float	LightYellow2[3]	=	{0.933333, 0.933333, 0.819608};
float	LightYellow3[3]	=	{0.803922, 0.803922, 0.705882};
float	LightYellow4[3]	=	{0.545098, 0.545098, 0.478431};
float	Yellow1[3]	=	{1, 1, 0};
float	Yellow2[3]	=	{0.933333, 0.933333, 0};
float	Yellow3[3]	=	{0.803922, 0.803922, 0};
float	Yellow4[3]	=	{0.545098, 0.545098, 0};
float	Gold1[3]	=	{1, 0.843137, 0};
float	Gold2[3]	=	{0.933333, 0.788235, 0};
float	Gold3[3]	=	{0.803922, 0.678431, 0};
float	Gold4[3]	=	{0.545098, 0.458824, 0};
float	Goldenrod1[3]	=	{1, 0.756863, 0.145098};
float	Goldenrod2[3]	=	{0.933333, 0.705882, 0.133333};
float	Goldenrod3[3]	=	{0.803922, 0.607843, 0.113725};
float	Goldenrod4[3]	=	{0.545098, 0.411765, 0.0784314};
float	DarkGoldenrod1[3]=	{1, 0.72549, 0.0588235};
float	DarkGoldenrod2[3]=	{0.933333, 0.678431, 0.054902};
float	DarkGoldenrod3[3]=	{0.803922, 0.584314, 0.0470588};
float	DarkGoldenrod4[3]=	{0.545098, 0.396078, 0.0313725};
float	RosyBrown1[3]	=	{1, 0.756863, 0.756863};
float	RosyBrown2[3]	=	{0.933333, 0.705882, 0.705882};
float	RosyBrown3[3]	=	{0.803922, 0.607843, 0.607843};
float	RosyBrown4[3]	=	{0.545098, 0.411765, 0.411765};
float	IndianRed1[3]	=	{1, 0.415686, 0.415686};
float	IndianRed2[3]	=	{0.933333, 0.388235, 0.388235};
float	IndianRed3[3]	=	{0.803922, 0.333333, 0.333333};
float	IndianRed4[3]	=	{0.545098, 0.227451, 0.227451};
float	Sienna1[3]	=	{1, 0.509804, 0.278431};
float	Sienna2[3]	=	{0.933333, 0.47451, 0.258824};
float	Sienna3[3]	=	{0.803922, 0.407843, 0.223529};
float	Sienna4[3]	=	{0.545098, 0.278431, 0.14902};
float	Burlywood1[3]	=	{1, 0.827451, 0.607843};
float	Burlywood2[3]	=	{0.933333, 0.772549, 0.568627};
float	Burlywood3[3]	=	{0.803922, 0.666667, 0.490196};
float	Burlywood4[3]	=	{0.545098, 0.45098, 0.333333};
float	Wheat1[3]	=	{1, 0.905882, 0.729412};
float	Wheat2[3]	=	{0.933333, 0.847059, 0.682353};
float	Wheat3[3]	=	{0.803922, 0.729412, 0.588235};
float	Wheat4[3]	=	{0.545098, 0.494118, 0.4};
float	Tan1[3]		=	{1, 0.647059, 0.309804};
float	Tan2[3]		=	{0.933333, 0.603922, 0.286275};
float	Tan3[3]		=	{0.803922, 0.521569, 0.247059};
float	Tan4[3]		=	{0.545098, 0.352941, 0.168627};
float	Chocolate1[3]	=	{1, 0.498039, 0.141176};
float	Chocolate2[3]	=	{0.933333, 0.462745, 0.129412};
float	Chocolate3[3]	=	{0.803922, 0.4, 0.113725};
float	Chocolate4[3]	=	{0.545098, 0.270588, 0.0745098};
float	Firebrick1[3]	=	{1, 0.188235, 0.188235};
float	Firebrick2[3]	=	{0.933333, 0.172549, 0.172549};
float	Firebrick3[3]	=	{0.803922, 0.14902, 0.14902};
float	Firebrick4[3]	=	{0.545098, 0.101961, 0.101961};
float	Brown1[3]	=	{1, 0.25098, 0.25098};
float	Brown2[3]	=	{0.933333, 0.231373, 0.231373};
float	Brown3[3]	=	{0.803922, 0.2, 0.2};
float	Brown4[3]	=	{0.545098, 0.137255, 0.137255};
float	Salmon1[3]	=	{1, 0.54902, 0.411765};
float	Salmon2[3]	=	{0.933333, 0.509804, 0.384314};
float	Salmon3[3]	=	{0.803922, 0.439216, 0.329412};
float	Salmon4[3]	=	{0.545098, 0.298039, 0.223529};
float	LightSalmon1[3]	=	{1, 0.627451, 0.478431};
float	LightSalmon2[3]	=	{0.933333, 0.584314, 0.447059};
float	LightSalmon3[3]	=	{0.803922, 0.505882, 0.384314};
float	LightSalmon4[3]	=	{0.545098, 0.341176, 0.258824};
float	Orange1[3]	=	{1, 0.647059, 0};
float	Orange2[3]	=	{0.933333, 0.603922, 0};
float	Orange3[3]	=	{0.803922, 0.521569, 0};
float	Orange4[3]	=	{0.545098, 0.352941, 0};
float	DarkOrange1[3]	=	{1, 0.498039, 0};
float	DarkOrange2[3]	=	{0.933333, 0.462745, 0};
float	DarkOrange3[3]	=	{0.803922, 0.4, 0};
float	DarkOrange4[3]	=	{0.545098, 0.270588, 0};
float	Coral1[3]	=	{1, 0.447059, 0.337255};
float	Coral2[3]	=	{0.933333, 0.415686, 0.313725};
float	Coral3[3]	=	{0.803922, 0.356863, 0.270588};
float	Coral4[3]	=	{0.545098, 0.243137, 0.184314};
float	Tomato1[3]	=	{1, 0.388235, 0.278431};
float	Tomato2[3]	=	{0.933333, 0.360784, 0.258824};
float	Tomato3[3]	=	{0.803922, 0.309804, 0.223529};
float	Tomato4[3]	=	{0.545098, 0.211765, 0.14902};
float	OrangeRed1[3]	=	{1, 0.270588, 0};
float	OrangeRed2[3]	=	{0.933333, 0.25098, 0};
float	OrangeRed3[3]	=	{0.803922, 0.215686, 0};
float	OrangeRed4[3]	=	{0.545098, 0.145098, 0};
float	Red1[3]		=	{1, 0, 0};
float	Red2[3]		=	{0.933333, 0, 0};
float	Red3[3]		=	{0.803922, 0, 0};
float	Red4[3]		=	{0.545098, 0, 0};
float	DeepPink1[3]	=	{1, 0.0784314, 0.576471};
float	DeepPink2[3]	=	{0.933333, 0.0705882, 0.537255};
float	DeepPink3[3]	=	{0.803922, 0.0627451, 0.462745};
float	DeepPink4[3]	=	{0.545098, 0.0392157, 0.313725};
float	HotPink1[3]	=	{1, 0.431373, 0.705882};
float	HotPink2[3]	=	{0.933333, 0.415686, 0.654902};
float	HotPink3[3]	=	{0.803922, 0.376471, 0.564706};
float	HotPink4[3]	=	{0.545098, 0.227451, 0.384314};
float	Pink1[3]	=	{1, 0.709804, 0.772549};
float	Pink2[3]	=	{0.933333, 0.662745, 0.721569};
float	Pink3[3]	=	{0.803922, 0.568627, 0.619608};
float	Pink4[3]	=	{0.545098, 0.388235, 0.423529};
float	LightPink1[3]	=	{1, 0.682353, 0.72549};
float	LightPink2[3]	=	{0.933333, 0.635294, 0.678431};
float	LightPink3[3]	=	{0.803922, 0.54902, 0.584314};
float	LightPink4[3]	=	{0.545098, 0.372549, 0.396078};
float	PaleVioletRed1[3]=	{1, 0.509804, 0.670588};
float	PaleVioletRed2[3]=	{0.933333, 0.47451, 0.623529};
float	PaleVioletRed3[3]=	{0.803922, 0.407843, 0.537255};
float	PaleVioletRed4[3]=	{0.545098, 0.278431, 0.364706};
float	Maroon1[3]	=	{1, 0.203922, 0.701961};
float	Maroon2[3]	=	{0.933333, 0.188235, 0.654902};
float	Maroon3[3]	=	{0.803922, 0.160784, 0.564706};
float	Maroon4[3]	=	{0.545098, 0.109804, 0.384314};
float	VioletRed1[3]	=	{1, 0.243137, 0.588235};
float	VioletRed2[3]	=	{0.933333, 0.227451, 0.54902};
float	VioletRed3[3]	=	{0.803922, 0.196078, 0.470588};
float	VioletRed4[3]	=	{0.545098, 0.133333, 0.321569};
float	Magenta1[3]	=	{1, 0, 1};
float	Magenta2[3]	=	{0.933333, 0, 0.933333};
float	Magenta3[3]	=	{0.803922, 0, 0.803922};
float	Magenta4[3]	=	{0.545098, 0, 0.545098};
float	Orchid1[3]	=	{1, 0.513725, 0.980392};
float	Orchid2[3]	=	{0.933333, 0.478431, 0.913725};
float	Orchid3[3]	=	{0.803922, 0.411765, 0.788235};
float	Orchid4[3]	=	{0.545098, 0.278431, 0.537255};
float	Plum1[3]	=	{1, 0.733333, 1};
float	Plum2[3]	=	{0.933333, 0.682353, 0.933333};
float	Plum3[3]	=	{0.803922, 0.588235, 0.803922};
float	Plum4[3]	=	{0.545098, 0.4, 0.545098};
float	MediumOrchid1[3]=	{0.878431, 0.4, 1};
float	MediumOrchid2[3]=	{0.819608, 0.372549, 0.933333};
float	MediumOrchid3[3]=	{0.705882, 0.321569, 0.803922};
float	MediumOrchid4[3]=	{0.478431, 0.215686, 0.545098};
float	DarkOrchid1[3]	=	{0.74902, 0.243137, 1};
float	DarkOrchid2[3]	=	{0.698039, 0.227451, 0.933333};
float	DarkOrchid3[3]	=	{0.603922, 0.196078, 0.803922};
float	DarkOrchid4[3]	=	{0.407843, 0.133333, 0.545098};
float	Purple1[3]	=	{0.607843, 0.188235, 1};
float	Purple2[3]	=	{0.568627, 0.172549, 0.933333};
float	Purple3[3]	=	{0.490196, 0.14902, 0.803922};
float	Purple4[3]	=	{0.333333, 0.101961, 0.545098};
float	MediumPurple1[3]=	{0.670588, 0.509804, 1};
float	MediumPurple2[3]=	{0.623529, 0.47451, 0.933333};
float	MediumPurple3[3]=	{0.537255, 0.407843, 0.803922};
float	MediumPurple4[3]=	{0.364706, 0.278431, 0.545098};
float   Thistle1[3]     =       {1, 0.882353, 1};
float	Thistle2[3]	=	{0.933333, 0.823529, 0.933333};
float	Thistle3[3]	=	{0.803922, 0.709804, 0.803922};
float	Thistle4[3]	=	{0.545098, 0.482353, 0.545098};
float	grey11[3]	=	{0.109804, 0.109804, 0.109804};
float	grey21[3]	=	{0.211765, 0.211765, 0.211765};
float	grey31[3]	=	{0.309804, 0.309804, 0.309804};
float	grey41[3]	=	{0.411765, 0.411765, 0.411765};
float	grey51[3]	=	{0.509804, 0.509804, 0.509804};
float	grey61[3]	=	{0.611765, 0.611765, 0.611765};
float	grey71[3]	=	{0.709804, 0.709804, 0.709804};
float	gray81[3]	=	{0.811765, 0.811765, 0.811765};
float	gray91[3]	=	{0.909804, 0.909804, 0.909804};
float	DarkGrey[3]	=	{0.662745, 0.662745, 0.662745};
float	DarkBlue[3]	=	{0, 0, 0.545098};
float	DarkCyan[3]	=	{0, 0.545098, 0.545098};
float	DarkMagenta[3]	=	{0.545098, 0, 0.545098};
float	DarkRed[3]	=	{0.545098, 0, 0};
float	LightGreen[3]	=	{0.564706, 0.933333, 0.564706};

#endif // _ALLCOLOR_
