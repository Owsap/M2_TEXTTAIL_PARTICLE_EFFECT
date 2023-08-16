/// 1.
// Add anywhere
#define /* @author: Owsap */ ENABLE_TEXTTAIL_PARTICLE_EFFECT // Text-Tail Particle Effect
#if defined(ENABLE_TEXTTAIL_PARTICLE_EFFECT)
#	define TEXTTAIL_PARTICLE_FRAMES 86 // Frame Count
#	define TEXTTAIL_PARTICLE_FRAME_DELAY 10 // Frame Delay
#	define TEXTTAIL_PARTICLE_FRAME_SCALE 0.50f // Frame Scale
#	define ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR // Random Title Color
#if defined(ENABLE_TEXTTAIL_RANDOM_TITLE_COLOR)
#	define TEXTTAIL_RANDOM_TITLE_COLOR_DELAY 15 // Random Title Delay
#	define TEXTTAIL_RANDOM_TITLE_COLOR_BY_ORDER // Random Title By Order
#endif
#endif
