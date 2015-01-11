package com.example.roberc4.internetswitch;

import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.Console;
import java.net.URI;
import java.net.URLEncoder;


public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }
    public void turnLEDON(View view)
    {
        new Light().execute("http://10.0.0.15:8888/$1");
    }
    public void turnLEDOFF(View view)
    {
        new Light().execute("http://10.0.0.15:8888/$2");
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    private class Light extends AsyncTask<String, Void, Void>
    {
        protected Void doInBackground(String... url)
        {
            Log.d("data", url[0]);
            try
            {
            HttpClient httpclient = new DefaultHttpClient();
            httpclient.execute(new HttpPost(url[0]));
            }
            catch (Exception e) {
                Log.d("exception", e.toString());
            }

            return null;
        }
    }
}

