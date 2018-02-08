var CetWebGLPlugin = {
	IsLogin: function()
	{
		return isCetLogin();
	},
	DoLogin: function(callBackGameObject, callBackFunction, userName, userPassword)
	{
		doCetLogin(Pointer_stringify(callBackGameObject), Pointer_stringify(callBackFunction), Pointer_stringify(userName), Pointer_stringify(userPassword));
	},
	GetUser: function(callBackGameObject, callBackFunction)
	{
		getCetUser(Pointer_stringify(callBackGameObject), Pointer_stringify(callBackFunction));
	},
	IsSubscription: function(callBackGameObject, callBackFunction)
	{
		isSubscription(Pointer_stringify(callBackGameObject), Pointer_stringify(callBackFunction));
	},
	GetUserId: function()
    {
		var returnStr = getCetUserId();
        var buffer = _malloc(lengthBytesUTF8(returnStr) + 1);
        writeStringToMemory(returnStr, buffer);
        return buffer;
    },
	WebGL_isSiteAllow: function()
	{
		if(window.location.hostname.indexOf(".cet.ac.il") == -1) {
			return false;
		} else {
			return true;
		}
	}

/*	
	Hello: function()
    {
        window.alert("Hello, world!");
    },
    HelloString: function(str)
    {
        window.alert(Pointer_stringify(str));
    },
    PrintFloatArray: function(array, size)
    {
        for(var i=0;i<size;i++)
            console.log(HEAPF32[(array>>2)+size]);
    },
    AddNumbers: function(x,y)
    {
        return x + y;
    },
    StringReturnValueFunction: function()
    {
        var returnStr = "bla";
        var buffer = _malloc(lengthBytesUTF8(returnStr) + 1);
        writeStringToMemory(returnStr, buffer);
        return buffer;
    },
    BindWebGLTexture: function(texture)
    {
        GLctx.bindTexture(GLctx.TEXTURE_2D, GL.textures[texture]);
    }
*/
};

mergeInto(LibraryManager.library, CetWebGLPlugin);
