var CetWebGLPlugin = {
	GAWebGL_TreckScreen: function(screenName)
	{
		GATreckScreen(Pointer_stringify(screenName));
	},
	GAWebGL_TreckEvent: function(category, action, label, value)
	{
		GATreckEvent(Pointer_stringify(category), Pointer_stringify(action));
	}
};
mergeInto(LibraryManager.library, CetWebGLPlugin);
