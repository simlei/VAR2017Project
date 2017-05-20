using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayMovieTextureOnUI : MonoBehaviour {

    public RawImage rawImage;

	// Use this for initialization
    void Start()
    {
        
        WebCamTexture webcamTexture = null;
        WebCamDevice[] devices = WebCamTexture.devices;
        for(int i=0; i < devices.Length; i++) {
            Debug.Log(devices[i].name);
            if(devices[i].name.Equals("HD Webcam C525"))
            {
                webcamTexture = new WebCamTexture("HD Webcam C525");
            } 
        }
        if (webcamTexture == null) {webcamTexture = new WebCamTexture(devices[0].name);}
        
        rawImage.texture = webcamTexture;
        rawImage.material.mainTexture = webcamTexture;
        webcamTexture.Play();
    }
	
}
