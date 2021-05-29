/* Copyright (C) 2021 @filterpaper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Graphical bongocat animation, driven by key press timer or WPM.
   It has left and right aligned cats optimized for both OLEDs.
   This code uses space-saving pixel differences, by rendering a
   base frame following by only changed pixels on animation frames.
   This should be rendered with OLED_ROTATION_270.

   Inspired by @j-inc's bongocat animation code
   (keyboards/kyria/keymaps/j-inc)

   Cat images courtesy of @plandevida

   Modified from @Dake's Modular Bongo Cat
   (https://github.com/Dakes/kyria/blob/main/keymaps/dakes/)
*/

#include "filterpaper.h"

#define IDLE_FRAMES 5
#define TAP_FRAMES 2
#define FRAME_DURATION 200 // Number of ms between frames
#define WIDTH OLED_DISPLAY_HEIGHT // 32 px when OLED is vertical


// Base animation frame that all subsequent ones will differ by pixels
#ifndef LEFTCAT
static uint16_t const base[] PROGMEM = {192, 33312, 33344, 33376, 33408, 33440, 33473, 33505, 33537, 33569, 33601, 33634, 33666, 33698, 33730, 33762, 33795, 33827, 33859, 33891, 33923, 33956, 33988, 34020, 34052, 34084, 34117, 34149, 34181, 34213, 34245, 34278, 34310, 34311, 34312, 34342, 34345, 34346, 34347, 34355, 34356, 34357, 34358, 34374, 34380, 34381, 34384, 34385, 34386, 34391, 34407, 34414, 34415, 34424, 34439, 34456, 34471, 34487, 34503, 34519, 34535, 34550, 34567, 34582, 34598, 34615, 34630, 34648, 34661, 34681, 34693, 34713, 34724, 34746, 34756, 34767, 34768, 34778, 34788, 34799, 34800, 34810, 34820, 34842, 34852, 34857, 34875, 34885, 34886, 34887, 34888, 34890, 34907, 34922, 34927, 34939, 34954, 34958, 34971, 34987, 34990, 35004, 35019, 35023, 35037, 35051, 35055, 35070, 35083, 35087, 35103, 35116, 35119, 35120, 35135, 35148, 35166, 35180, 35186, 35187, 35196, 35197, 35212, 35218, 35219, 35226, 35227, 35244, 35257, 35277, 35288, 35309, 35319, 35340, 35351, 35372, 35382, 35403, 35413, 35435, 35444, 35467, 35475, 35499, 35506, 35531, 35537, 35563, 35567, 35568, 35596, 35597, 35598, 35599, 35631, 35663, 35696, 35728, 35760, 35792, 35825, 35857, 35889, 35921, 35954, 35986, 36018, 36050, 36083, 36115, 36147, 36179, 36212, 36244, 36276, 36308, 36340, 36373, 36405, 36437, 36469, 36501, 36534, 36566, 36598, 36630, 36663, 36695, 36727, 36759, 36792, 36824, 36856};
#endif
#ifndef RIGHTCAT
static uint16_t const left_base[] PROGMEM = {192, 33343, 33375, 33407, 33439, 33471, 33502, 33534, 33566, 33598, 33630, 33661, 33693, 33725, 33757, 33789, 33820, 33852, 33884, 33916, 33948, 33979, 34011, 34043, 34075, 34107, 34138, 34170, 34202, 34234, 34266, 34297, 34327, 34328, 34329, 34345, 34346, 34347, 34348, 34356, 34357, 34358, 34361, 34376, 34381, 34382, 34383, 34386, 34387, 34393, 34407, 34416, 34417, 34424, 34439, 34456, 34472, 34488, 34504, 34520, 34537, 34552, 34569, 34584, 34600, 34617, 34631, 34649, 34662, 34682, 34694, 34714, 34725, 34747, 34757, 34767, 34768, 34779, 34789, 34799, 34800, 34811, 34821, 34843, 34852, 34870, 34875, 34884, 34901, 34903, 34904, 34905, 34906, 34916, 34928, 34933, 34948, 34961, 34965, 34979, 34993, 34996, 35010, 35024, 35028, 35041, 35056, 35060, 35072, 35088, 35092, 35104, 35119, 35120, 35123, 35137, 35155, 35170, 35171, 35180, 35181, 35187, 35204, 35205, 35212, 35213, 35219, 35238, 35251, 35271, 35282, 35304, 35314, 35336, 35347, 35369, 35379, 35402, 35412, 35435, 35444, 35468, 35476, 35501, 35508, 35534, 35540, 35567, 35568, 35572, 35600, 35601, 35602, 35603, 35632, 35664, 35695, 35727, 35759, 35791, 35822, 35854, 35886, 35918, 35949, 35981, 36013, 36045, 36076, 36108, 36140, 36172, 36203, 36235, 36267, 36299, 36331, 36362, 36394, 36426, 36458, 36490, 36521, 36553, 36585, 36617, 36648, 36680, 36712, 36744, 36775, 36807, 36839};
#endif


// Loop array to render pixels on OLED
static void render_array(uint16_t const *frame) {
	// First array element is the size
	uint16_t const size = pgm_read_word(&(frame[0]));
	for (uint16_t i = size; i > 0; --i) {
		uint16_t cur_px = pgm_read_word(&(frame[i]));
		// Get pixel state bit
		bool const on = (cur_px & ( 1 << 15 )) >> 15;
		// Remove pixel state bit
		cur_px &= ~(1UL << 15);
		oled_write_pixel(cur_px % WIDTH, cur_px / WIDTH, on);
	}
}


static void render_frames(uint16_t const *base, uint16_t const *diff) {
	render_array(base);
	render_array(diff);
}


static void render_cat_idle(void) {
	// Idle frames pixel differences
#ifndef LEFTCAT
	static uint16_t const idle_diff_0[] PROGMEM = {0};
	static uint16_t const idle_diff_1[] PROGMEM = {105, 34354, 1590, 34379, 1613, 34383, 1618, 34390, 1623, 34413, 1647, 34423, 1656, 34455, 1688, 34486, 1719, 34518, 1751, 34549, 1782, 34581, 1814, 34614, 1847, 34647, 1880, 34680, 1913, 34712, 1945, 34745, 1978, 34766, 2000, 34777, 2010, 34798, 2032, 34809, 2042, 34841, 2074, 34874, 2107, 34906, 2139, 34926, 2159, 34938, 2171, 34957, 2190, 34970, 2203, 34989, 2222, 35003, 2236, 35022, 2255, 35036, 2269, 35054, 2287, 35069, 2302, 35086, 2319, 35102, 2335, 35118, 2352, 35134, 2367, 35165, 2398, 35185, 2419, 35195, 2429, 35217, 2451, 35225, 2459, 35256, 2489, 35287, 2520, 35318, 2551, 35350, 2583, 35381, 2614, 35412, 2645, 35443, 2676, 35474, 2707, 35505, 2738, 35536, 2769, 2800};
	static uint16_t const idle_diff_2[] PROGMEM = {31, 34313, 1577, 34348, 1589, 1590, 1612, 1616, 34389, 1623, 34416, 34422, 1656, 34454, 1688, 34486, 1719, 34518, 1751, 35003, 2236, 35036, 2269, 35068, 2302, 35101, 2335, 35133, 2367, 35165, 2398, 2429};
	static uint16_t const idle_diff_3[] PROGMEM = {21, 1590, 34390, 1623, 34423, 1656, 34455, 1688, 34486, 1719, 34518, 1751, 35036, 2269, 35069, 2302, 35102, 2335, 35134, 2367, 2428, 35228};
	static uint16_t const *idle_diff[IDLE_FRAMES] = {
		idle_diff_0,
		idle_diff_0,
		idle_diff_1,
		idle_diff_2,
		idle_diff_3
	};
#endif
#ifndef RIGHTCAT
	static uint16_t const left_idle_diff_0[] PROGMEM = {0};
	static uint16_t const left_idle_diff_1[] PROGMEM = {105, 1577, 34349, 1608, 34377, 1613, 34384, 1618, 34388, 1639, 34408, 1648, 34418, 1671, 34440, 1704, 34473, 1736, 34505, 1769, 34538, 1801, 34570, 1832, 34601, 1863, 34632, 1894, 34663, 1926, 34695, 1957, 34726, 1989, 34758, 1999, 34769, 2021, 34790, 2031, 34801, 2053, 34822, 2084, 34853, 2116, 34885, 2148, 34917, 2160, 34929, 2180, 34949, 2193, 34962, 2211, 34980, 2225, 34994, 2242, 35011, 2256, 35025, 2273, 35042, 2288, 35057, 2304, 35073, 2320, 35089, 2336, 35105, 2351, 35121, 2369, 35138, 2402, 35172, 2412, 35182, 2436, 35206, 2444, 35214, 2470, 35239, 2503, 35272, 2536, 35305, 2568, 35337, 2601, 35370, 2634, 35403, 2667, 35436, 2700, 35469, 2733, 35502, 2766, 35535, 2799};
	static uint16_t const left_idle_diff_2[] PROGMEM = {31, 34326, 1577, 1578, 34355, 1590, 1608, 34378, 1615, 1619, 1639, 34409, 34415, 1671, 34441, 1704, 34473, 1736, 34505, 2211, 34980, 2242, 35011, 2273, 35043, 2304, 35074, 2336, 35106, 2369, 35138, 2402};
	static uint16_t const left_idle_diff_3[] PROGMEM = {21, 1577, 1608, 34377, 1639, 34408, 1671, 34440, 1704, 34473, 1736, 34505, 2242, 35011, 2273, 35042, 2304, 35073, 2336, 35105, 2403, 35203};
	static uint16_t const *left_idle_diff[IDLE_FRAMES] = {
		left_idle_diff_0,
		left_idle_diff_0,
		left_idle_diff_1,
		left_idle_diff_2,
		left_idle_diff_3
	};
#endif

	static uint8_t current_frame = 0;
	current_frame = (current_frame + 1 > IDLE_FRAMES - 1) ? 0 : current_frame + 1;

#if defined(LEFTCAT)
	render_frames(left_base, left_idle_diff[current_frame]);
#elif defined(RIGHTCAT)
	render_frames(base, idle_diff[current_frame]);
#else
	is_keyboard_left() ? render_frames(left_base, left_idle_diff[current_frame]) : render_frames(base, idle_diff[current_frame]);
#endif
}


static void render_cat_prep(void) {
	// Prep frames pixel differences
#ifndef LEFTCAT
	static uint16_t const prep_diff_0[] PROGMEM = {82, 34507, 34508, 34541, 34542, 34573, 34575, 1830, 34600, 34603, 34604, 34608, 1862, 34632, 34635, 34636, 34639, 34640, 1893, 34664, 34669, 34672, 1925, 34696, 34697, 34702, 34703, 1956, 34729, 34730, 34731, 34732, 34733, 1988, 34761, 2020, 34793, 2052, 34825, 2084, 2117, 2118, 2119, 2120, 2572, 35341, 35344, 35345, 35346, 2604, 35373, 35379, 35380, 2635, 35405, 35414, 2667, 35437, 35447, 2699, 35470, 35474, 35479, 2731, 35502, 35507, 35509, 35511, 2763, 35534, 2769, 35543, 2795, 35572, 35574, 2828, 2829, 2830, 35601, 35602, 35603, 35604, 35605};
	static uint16_t const *prep_diff[] = {
		prep_diff_0
	};
#endif
#ifndef RIGHTCAT
	static uint16_t const left_prep_diff_0[] PROGMEM = {82, 34515, 34516, 34545, 34546, 34576, 34578, 34607, 34611, 34612, 34615, 1849, 34639, 34640, 34643, 34644, 34647, 1881, 34671, 34674, 34679, 1914, 34704, 34705, 34710, 34711, 1946, 34738, 34739, 34740, 34741, 34742, 1979, 34774, 2011, 34806, 2043, 34838, 2075, 2107, 2135, 2136, 2137, 2138, 35341, 35342, 35343, 35346, 2579, 35371, 35372, 35378, 2611, 35401, 35410, 2644, 35432, 35442, 2676, 35464, 35469, 35473, 2708, 35496, 35498, 35500, 35505, 2740, 35528, 2766, 35537, 2772, 35561, 35563, 2804, 35594, 35595, 35596, 35597, 35598, 2833, 2834, 2835};
	static uint16_t const *left_prep_diff[] = {
		left_prep_diff_0
	};
#endif

#if defined(LEFTCAT)
	render_frames(left_base, left_prep_diff[0]);
#elif defined(RIGHTCAT)
	render_frames(base, prep_diff[0]);
#else
	is_keyboard_left() ? render_frames(left_base, left_prep_diff[0]) : render_frames(base, prep_diff[0]);
#endif
}


static void render_cat_tap(void) {
	// Tap frames pixel differences
#ifndef LEFTCAT
	static uint16_t const tap_diff_0[] PROGMEM = {156, 34507, 34508, 34541, 34542, 34573, 34575, 1830, 34600, 34603, 34604, 34608, 1862, 34632, 34635, 34636, 34639, 34640, 1893, 34664, 34669, 34672, 1925, 34697, 34702, 34703, 1956, 34729, 34730, 34731, 34732, 34733, 1988, 34761, 2020, 34793, 2052, 34825, 2084, 2117, 2118, 2119, 2120, 35542, 35543, 35544, 35545, 35546, 35547, 35548, 35573, 35574, 35575, 35576, 35577, 35578, 35579, 35580, 35605, 35606, 35607, 35608, 35609, 35610, 35611, 35612, 35639, 35640, 35641, 35642, 35643, 35644, 35658, 35659, 35660, 35661, 35689, 35690, 35691, 35692, 35693, 35698, 35699, 35700, 35720, 35721, 35722, 35723, 35724, 35725, 35730, 35731, 35732, 35733, 35751, 35752, 35753, 35754, 35755, 35756, 35757, 35762, 35763, 35764, 35765, 35766, 35782, 35783, 35784, 35785, 35786, 35787, 35788, 35789, 35795, 35796, 35797, 35798, 35799, 35814, 35815, 35816, 35817, 35818, 35819, 35820, 35821, 35827, 35828, 35829, 35830, 35831, 35832, 35848, 35849, 35850, 35851, 35852, 35853, 35859, 35860, 35861, 35862, 35863, 35864, 35882, 35883, 35884, 35885, 35892, 35893, 35894, 35895, 35916, 35917, 35924, 35925};
	static uint16_t const tap_diff_1[] PROGMEM = {72, 34337, 34338, 34339, 34340, 34369, 34370, 34371, 34372, 34401, 34402, 34403, 34404, 34433, 34434, 34435, 34436, 34465, 34466, 34467, 34468, 34497, 34498, 34499, 34500, 34530, 34531, 34532, 34562, 34563, 34816, 34848, 34880, 34912, 2572, 35341, 35344, 35345, 35346, 2604, 35373, 35379, 35380, 2635, 35405, 35414, 2667, 35437, 35447, 2699, 35470, 35474, 35479, 2731, 35502, 35507, 35509, 35511, 2763, 35534, 2769, 35543, 2795, 35572, 35574, 2828, 2829, 2830, 35601, 35602, 35603, 35604, 35605};
	static uint16_t const *tap_diff[TAP_FRAMES] = {
		tap_diff_0,
		tap_diff_1
	};
#endif
#ifndef RIGHTCAT
	static uint16_t const left_tap_diff_0[] PROGMEM = {156, 34515, 34516, 34545, 34546, 34576, 34578, 34607, 34611, 34612, 34615, 1849, 34639, 34640, 34643, 34644, 34647, 1881, 34671, 34674, 34679, 1914, 34704, 34705, 34710, 1946, 34738, 34739, 34740, 34741, 34742, 1979, 34774, 2011, 34806, 2043, 34838, 2075, 2107, 2135, 2136, 2137, 2138, 35523, 35524, 35525, 35526, 35527, 35528, 35529, 35555, 35556, 35557, 35558, 35559, 35560, 35561, 35562, 35587, 35588, 35589, 35590, 35591, 35592, 35593, 35594, 35619, 35620, 35621, 35622, 35623, 35624, 35666, 35667, 35668, 35669, 35691, 35692, 35693, 35698, 35699, 35700, 35701, 35702, 35722, 35723, 35724, 35725, 35730, 35731, 35732, 35733, 35734, 35735, 35753, 35754, 35755, 35756, 35757, 35762, 35763, 35764, 35765, 35766, 35767, 35768, 35784, 35785, 35786, 35787, 35788, 35794, 35795, 35796, 35797, 35798, 35799, 35800, 35801, 35815, 35816, 35817, 35818, 35819, 35820, 35826, 35827, 35828, 35829, 35830, 35831, 35832, 35833, 35847, 35848, 35849, 35850, 35851, 35852, 35858, 35859, 35860, 35861, 35862, 35863, 35880, 35881, 35882, 35883, 35890, 35891, 35892, 35893, 35914, 35915, 35922, 35923};
	static uint16_t const left_tap_diff_1[] PROGMEM = {72, 34363, 34364, 34365, 34366, 34395, 34396, 34397, 34398, 34427, 34428, 34429, 34430, 34459, 34460, 34461, 34462, 34491, 34492, 34493, 34494, 34523, 34524, 34525, 34526, 34555, 34556, 34557, 34588, 34589, 34847, 34879, 34911, 34943, 35341, 35342, 35343, 35346, 2579, 35371, 35372, 35378, 2611, 35401, 35410, 2644, 35432, 35442, 2676, 35464, 35469, 35473, 2708, 35496, 35498, 35500, 35505, 2740, 35528, 2766, 35537, 2772, 35561, 35563, 2804, 35594, 35595, 35596, 35597, 35598, 2833, 2834, 2835};
	static uint16_t const *left_tap_diff[TAP_FRAMES] = {
		left_tap_diff_0,
		left_tap_diff_1
	};
#endif
	static uint8_t current_frame = 0;
//	current_frame = (current_frame + 1 > TAP_FRAMES - 1) ? 0 : current_frame + 1;
	current_frame = (current_frame + 1) & 1;

#if defined(LEFTCAT)
	render_frames(left_base, left_tap_diff[current_frame]);
#elif defined(RIGHTCAT)
	render_frames(base, tap_diff[current_frame]);
#else
	is_keyboard_left() ? render_frames(left_base, left_tap_diff[current_frame]) : render_frames(base, tap_diff[current_frame]);
#endif
}


void render_bongocat(void) {
#ifdef WPM_ENABLE
	static uint8_t prev_wpm = 0;
	static uint32_t tap_timer = 0; // WPM triggered
	if (get_current_wpm() > prev_wpm) { tap_timer = timer_read32(); }
	prev_wpm = get_current_wpm();
#else
	extern uint32_t tap_timer; // process_record_user() triggered
#endif
	// Elapsed time between key presses
	uint32_t keystroke = timer_elapsed32(tap_timer);
	static uint16_t anim_timer = 0;

	void animation_phase(void) {
		oled_clear();
		if (keystroke < FRAME_DURATION*2) { render_cat_tap(); }
		else if (keystroke < FRAME_DURATION*8) { render_cat_prep(); }
		else { render_cat_idle(); }
	}

	if (keystroke > OLED_TIMEOUT) { oled_off(); }
	else if (timer_elapsed(anim_timer) > FRAME_DURATION) {
		anim_timer = timer_read();
		animation_phase();
	}
}
