var bucketName = 'ftm-state';
var bucketRegion = 'eu-west-1';
var IdentityPoolId = 'eu-west-1:627f4e2a-9682-4d5d-9ee3-5a41ea9abc03';

AWS.config.update({
  region: bucketRegion,
  credentials: new AWS.CognitoIdentityCredentials({
	IdentityPoolId: IdentityPoolId
  })
});

var s3 = new AWS.S3({
  apiVersion: '2006-03-01',
  params: {Bucket: bucketName}
});


function getS3File(callBackGameObject, callBackFunction, fileName) {
	var params = {
		Key: fileName
	};
	s3.getObject(params, function(err, data) {
		if (err) {
			console.log(err, err.stack); // an error occurred
			gameInstance.SendMessage(callBackGameObject, callBackFunction, "{}");
		} else {
			console.log(data);           // successful response
			var content = String.fromCharCode.apply(null, new Uint16Array(data.Body));
			
			if(data.ContentType == "application/xml") {
				gameInstance.SendMessage(callBackGameObject, callBackFunction, "{}");
			} else {
				gameInstance.SendMessage(callBackGameObject, callBackFunction, content);	
			}
		}
	});
}


function setS3File(callBackGameObject, callBackFunction, fileName, content) {
	var params = {
		Key: fileName,
		Body: content,
		ACL: 'public-read'
	};
	if(fileName != "" && content != "") {
		s3.upload(params, function(err, data) {
			if (err) {
				console.log(err, err.stack); // an error occurred
				var res = "{\"ok\":false}";
				gameInstance.SendMessage(callBackGameObject, callBackFunction, res);
	//			alert('There was an error uploading your photo: ', err.message);
			} else {
	//			alert('Successfully uploaded photo.');	
				var res = "{\"ok\":true}";
				gameInstance.SendMessage(callBackGameObject, callBackFunction, res);
			}
		});
	} else {
		var res = "{\"ok\":false}";
		gameInstance.SendMessage(callBackGameObject, callBackFunction, res);
	}
}