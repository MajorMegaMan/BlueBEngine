#include "Input.h"

namespace BBB
{
	namespace Input
	{
		namespace
		{
			const int _keyActionsSize = KEY_UNKNOWN + 1;
			KeyAction _keyActions[_keyActionsSize];

			void default_key_action(GLFWwindow* window, int scancode, int action, int mods)
			{
				// This is intentionally empty
			}

			void default_scroll_action(GLFWwindow* window, double x, double y)
			{
				// This is intentionally empty
			}

			GLFWscrollfun _scrollAction = default_scroll_action;
		}

		void init_key_actions()
		{
			for (int i = 0; i < KEY_UNKNOWN + 1; i++)
			{
				_keyActions[i] = default_key_action;
			}
		}

		void set_key_action(int key, KeyAction action)
		{
			int index = (key + _keyActionsSize) % _keyActionsSize;
			_keyActions[index] = action;
		}

		void invoke_key_action(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			// ensure the index matches the correct action
			int index = (key + _keyActionsSize) % _keyActionsSize;
			_keyActions[index](window, scancode, action, mods);
		}

		void set_scroll_action(GLFWscrollfun action)
		{
			_scrollAction = action;
		}

		void invoke_scroll_action(GLFWwindow* window, double x, double y)
		{
			_scrollAction(window, x, y);
		}
	}
}