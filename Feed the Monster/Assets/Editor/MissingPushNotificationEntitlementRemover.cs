// C# example:	
using UnityEngine;
using UnityEditor;
using UnityEditor.Callbacks;
using System.IO;
using System.Text.RegularExpressions;

public class MissingPushNotificationEntitlementRemover {

	public static string appControllerFile = "UnityAppController.mm";
	// this matches (void)application:did..something..Notification..something... methods declaration
	private static string regexpForNotificationMethods = "-\\s?\\(void\\)application:\\(UIApplication\\s?\\*\\)application\\sdid.+RemoteNotification.+\\n?{[^-|#.+]+";
	
	[PostProcessBuild]
	public static void OnPostprocessBuild(BuildTarget target, string pathToBuiltProject) {
		if (target != BuildTarget.iOS) {
			return;
		}

		Debug.Log("Running Push Notification Entitlement Warning Remover...");

		// check if app controller file exists
		string classesDirectory = Path.Combine(pathToBuiltProject, "Classes");
		string pathToAppController = Path.Combine(classesDirectory, appControllerFile);

		bool fileExists = File.Exists(pathToAppController);

		if (!fileExists) {
			Debug.Log("App Controller file doesn't exist.");
			return;
		}

		string code = File.ReadAllText(pathToAppController);
		string codeWithDeletedNotificationsMethod = Regex.Replace(code, regexpForNotificationMethods, "");

		File.WriteAllText(pathToAppController, codeWithDeletedNotificationsMethod);
		Debug.Log("Push Notification Entitlement Warning Remover Completed");
	}
		
}
