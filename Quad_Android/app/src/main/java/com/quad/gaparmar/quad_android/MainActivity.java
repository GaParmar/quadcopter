package com.quad.gaparmar.quad_android;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity implements
        SeekBar.OnSeekBarChangeListener
{
    private final UUID PORT_UUID = UUID.fromString
            ("00001101-0000-1000-8000-00805f9b34fb");
    SeekBar throttle, yaw, pitch, roll;
    Button power;
    private BluetoothDevice device;
    private BluetoothSocket socket;
    private OutputStream outputStream;
    private Toast toast;

    @Override
    protected void onCreate (Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        throttle = (SeekBar) findViewById(R.id.seekBarThrottle);
        yaw = (SeekBar) findViewById(R.id.seekBarYaw);
        pitch = (SeekBar) findViewById(R.id.seekBarPitch);
        roll = (SeekBar) findViewById(R.id.seekBarRoll);
        power = (Button) findViewById(R.id.power);
        power.setEnabled(true);

    }

    public void onClickStart (View view)
    {
        boolean found = false;
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter
                .getDefaultAdapter();
        if (bluetoothAdapter == null)
        {
            Toast.makeText(getApplicationContext(), "Device doesnt " +
                    "Support Bluetooth", Toast.LENGTH_SHORT).show();
        }
        Set<BluetoothDevice> bondedDevices = bluetoothAdapter
                .getBondedDevices();
        if (bondedDevices.isEmpty())
        {
            Toast.makeText(getApplicationContext(), "No paired devices " +
                    "found", Toast.LENGTH_SHORT).show();
        }
        else
        {
            for (BluetoothDevice iterator : bondedDevices)
            {
                if (iterator.getName().equals("HC-05"))
                {
                    device = iterator;
                    Toast.makeText(getApplicationContext(), "drone " +
                            "connected", Toast.LENGTH_SHORT).show();
                    found = true;
                }
            }
        }

        if (found)
        {
            found = false;
            try
            {
                socket = device.createRfcommSocketToServiceRecord
                        (PORT_UUID);
                socket.connect();
                outputStream = socket.getOutputStream();
                found = true;
            } catch (IOException e)
            {
                e.printStackTrace();
            }
            if (found)
            {
                throttle.setOnSeekBarChangeListener(this);
                roll.setOnSeekBarChangeListener(this);
                pitch.setOnSeekBarChangeListener(this);
                yaw.setOnSeekBarChangeListener(this);
            }
        }
    }

    @Override
    public boolean onCreateOptionsMenu (Menu menu)
    {

        return true;
    }

    @Override
    public boolean onOptionsItemSelected (MenuItem item)
    {


        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onProgressChanged (SeekBar seekBar, int
            progress, boolean fromUser)
    {
        Toast.makeText(getApplicationContext(), "1", Toast.LENGTH_SHORT)
                .show();
        //toast.cancel();
        String trans = "";
        switch (seekBar.getId())
        {
            case R.id.seekBarThrottle:
                trans = "t";
                break;
            case R.id.seekBarRoll:
                trans = "r";
                break;
            case R.id.seekBarPitch:
                trans = "p";
                break;
            case R.id.seekBarYaw:
                trans = "y";
                break;
        }
        //trans += progress;
        //trans += "\0\n";
        try
        {
            outputStream.write(trans.getBytes());
            outputStream.write(String.valueOf(progress).getBytes());
        } catch (IOException e)
        {
            finish();
        }
        toast = Toast.makeText(getApplicationContext(), trans, Toast
                .LENGTH_SHORT);
        toast.show();

    }

    @Override
    public void onStartTrackingTouch (SeekBar seekBar)
    {
    }

    @Override
    public void onStopTrackingTouch (SeekBar seekBar)
    {
    }
}