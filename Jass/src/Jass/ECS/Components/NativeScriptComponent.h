#ifndef NATIVE_SCRIPT_COMPONENT_H
#define NATIVE_SCRIPT_COMPONENT_H

namespace Jass {

	class Scriptable;

	struct NativeScriptComponent
	{
		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent& other) = default;

		struct NativeScript {
			Scriptable* Instance = nullptr;
			Scriptable* (*Instantiate)();
			void (*Destroy)(NativeScript&);
		};

		std::vector<NativeScript> NativeScripts;
	};

}

#endif // !NATIVE_SCRIPT_COMPONENT_H
