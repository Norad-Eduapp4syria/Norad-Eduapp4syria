/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

// for zip
import java.io.*;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;


import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.EnumSet;
import java.util.Locale;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.annotation.TargetApi;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Point;
import android.Manifest;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

/*
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.android.gms.plus.Plus;
*/

//import com.google.example.games.basegameutils.BaseGameUtils;
import android.os.Vibrator;
import android.content.Context;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.provider.MediaStore;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.File;
import java.io.FileOutputStream;

import java.util.Date;
import java.util.Calendar;
import java.util.TimeZone;
import java.text.DateFormat;


public class AppActivity extends Cocos2dxActivity {

	private static AppActivity _appActiviy;

	private static final int RESULT_LOAD_CAMERA = 21;
	private static String imageName = "";
	private static int imageWidth = 100, imageHeight = 100;
	private static String storageDirectory = "";


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		_appActiviy = this;
	}

	protected void onStart() {
		super.onStart();
	}

	protected void onStop() {
		super.onStop();
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

    @Override
    protected void onNewIntent(Intent intent) {
    	super.onNewIntent(intent);
    }

	@Override
	protected void onActivityResult(int requestCode, int responseCode, Intent intent) {
		super.onActivityResult(requestCode, responseCode, intent);
		System.out.println("responseCode =  "+responseCode+"  :: intent = "+intent);
		System.out.println("onActivityResult() " + requestCode + "  ::: " + responseCode);
		if (requestCode == RESULT_LOAD_CAMERA) {
			if(responseCode == RESULT_OK) {
				System.out.println("responseCode == RESULT_OK");
				File file = new File(storageDirectory +  "/" + imageName);
				try {
					Bitmap original = BitmapFactory.decodeFile(file.getAbsolutePath());
					original = Bitmap.createScaledBitmap(original, imageWidth, imageHeight, true);
					FileOutputStream stream;
					stream = _appActiviy.getApplicationContext().openFileOutput(imageName, Context.MODE_PRIVATE);
					// Write bitmap to file using JPEG or PNG and 80% quality hint for JPEG.
					original.compress(Bitmap.CompressFormat.PNG, 100, stream);
					original.recycle(); //ensure the image is freed;
					stream.close();

					callCameraResponse(imageName);

				} catch(Exception ex) {
					callCameraResponse("");
				}
			}
			else {
				callCameraResponse("");
			}
			/*if(responseCode == RESULT_OK && null != intent) {
				try {
					Bitmap original = (Bitmap) intent.getParcelableExtra("data"); //intent.getExtras().get("data");
					//FileOutputStream stream = new FileOutputStream("/storage/emulated/0/Pictures/profile_photo.png");
					original = Bitmap.createScaledBitmap(original, imageWidth, imageHeight, true);
					FileOutputStream stream;
					stream = _appActiviy.getApplicationContext().openFileOutput(imageName, Context.MODE_PRIVATE);
					// Write bitmap to file using JPEG or PNG and 80% quality hint for JPEG.
					original.compress(Bitmap.CompressFormat.PNG, 100, stream);
					original.recycle(); //ensure the image is freed;
					stream.close();

					callCameraResponse(imageName);

				} catch(Exception ex) {
					callCameraResponse("");
				}
            }
            else {
				callCameraResponse("");
			}*/

		}
	}

    public static void saveImage(String name, int width, int height) {
        System.out.println("saveImage");
        File imgFile = new  File(name);
        Bitmap myBitmap = BitmapFactory.decodeFile(imgFile.getAbsolutePath());
        MediaStore.Images.Media.insertImage(_appActiviy.getApplicationContext().getContentResolver(), myBitmap, "" , "");
        
    }
        
    public static void createNecessaryFolders(String folderPath, int width, int height) {
    
        File directoryBase = new File("/sdcard/" + folderPath);
        
        if(!directoryBase.exists())
        {
            directoryBase.mkdir();
 	     File directoryLogs = new File("/sdcard/" + folderPath + "/Logs");
            directoryLogs.mkdir();
	     File directoryDb = new File("/sdcard/" + folderPath + "/Databases");
            directoryDb.mkdir();
        }
    }

    public static void createFolder(String folderPath, int width, int height) {
        System.out.println("try to create createFolder " + folderPath);
        File directory = new File("/sdcard/" + folderPath);
        
        if(!directory.exists())
        {
            if(directory.mkdir())
            {
                System.out.println("folder " + folderPath + " created.");
            } else {
                System.out.println("folder " + folderPath + " not created.");
            }
        }
    }
    
    public static void openCamera(String name, int width, int height) {
		int result = ContextCompat.checkSelfPermission(_appActiviy, Manifest.permission.CAMERA);
		int result2 = ContextCompat.checkSelfPermission(_appActiviy, Manifest.permission.WRITE_EXTERNAL_STORAGE);
		if (result == PackageManager.PERMISSION_GRANTED && result2 == PackageManager.PERMISSION_GRANTED){
			getStorageDirectory();
			imageName = name;
			imageWidth = width;
			imageHeight = height;
			Intent cameraIntent = new Intent(android.provider.MediaStore.ACTION_IMAGE_CAPTURE);
			File file = new File(storageDirectory +  "/" + imageName);
			Uri outputFileUri = Uri.fromFile(file);
			cameraIntent.putExtra(MediaStore.EXTRA_OUTPUT, outputFileUri);
    		_appActiviy.startActivityForResult(cameraIntent, RESULT_LOAD_CAMERA);
		} else {
			requestPermissionForCamera();
        }
	}

	static public void requestPermissionForCamera(){
		if (ActivityCompat.shouldShowRequestPermissionRationale(_appActiviy, Manifest.permission.CAMERA) ||
			ActivityCompat.shouldShowRequestPermissionRationale(_appActiviy, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
			//Toast.makeText(_appActiviy.getApplicationContext(), "Camera permission needed. Please allow in App Settings for additional functionality.", Toast.LENGTH_LONG).show();
		} else {
			ActivityCompat.requestPermissions(_appActiviy,new String[]{Manifest.permission.CAMERA,Manifest.permission.WRITE_EXTERNAL_STORAGE},33);
		}
    }

	static public void getStorageDirectory() {
		if((Environment.getExternalStorageState() != Environment.MEDIA_BAD_REMOVAL &&
				Environment.getExternalStorageState() != Environment.MEDIA_MOUNTED_READ_ONLY &&
				Environment.getExternalStorageState() != Environment.MEDIA_NOFS &&
				Environment.getExternalStorageState() != Environment.MEDIA_REMOVED &&
				Environment.getExternalStorageState() != Environment.MEDIA_UNMOUNTABLE &&
				Environment.getExternalStorageState() != Environment.MEDIA_UNMOUNTED))
		{
			/**
			 * Use getExternalStorageDirectory() to save the cropped picture because we cannot use
			 * the folder /data/data/... to save temporary picture.
			 */

			storageDirectory = Environment.getExternalStorageDirectory().toString();
            storageDirectory = "/sdcard";
			File directory = new File(storageDirectory + "/Kukua/Photos");

			if(!directory.exists())
			{
				if(directory.mkdir())
				{
					storageDirectory = storageDirectory + "/Kukua/Photos";
					System.out.println("Folder " + storageDirectory + " does not exist, folder created.");
				}
				else
					System.out.println("Folder " + storageDirectory + " does not exist, cannot create folder.");
			}
			else
				storageDirectory = storageDirectory + "/Kukua/Photos";
		}
	}


	public static native void callCameraResponse(String imagePath);
    
    
    
    
    public static void unZipArchiveToFolder(String archivePath, String destFolderPath)
    {
        System.out.println("******* ZIP MANAGER");
        InputStream is;
        ZipInputStream zis;
        try
        {
            String filename;
            is = new FileInputStream(archivePath);
            zis = new ZipInputStream(new BufferedInputStream(is));
            ZipEntry ze;
            byte[] buffer = new byte[1024];
            int count;
            
            while ((ze = zis.getNextEntry()) != null)
            {
                // zapis do souboru
                filename = ze.getName();
                System.out.println("******* ZIP MANAGER nuovo file ");
                
                // Need to create directories if not exists, or
                // it will generate an Exception...
                if (ze.isDirectory()) {
                    File fmd = new File(destFolderPath + filename);
                    fmd.mkdirs();
                    continue;
                }
                
                System.out.println("******* ZIP MANAGER file da copiare : " + destFolderPath + filename);
                
                FileOutputStream fout = new FileOutputStream(destFolderPath + filename);
                
                // cteni zipu a zapis
                while ((count = zis.read(buffer)) != -1)
                {
                    fout.write(buffer, 0, count);
                }
                
                System.out.println("******* ZIP MANAGER nuovo file copiato !!!");
                
                fout.close();
                zis.closeEntry();
            }
            
            zis.close();
        } 
        catch(IOException e)
        {
            System.out.println("******* ZIP MANAGER errore!!!");   
            e.printStackTrace();
        }
        
    }

    
    
    
}
