/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pt.pkg2.java.swing;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

public class FileExt extends File
{
    FileExt(File plik)
    {
        super(plik.getPath());
    }

    public String fileInfo()
    {
        SimpleDateFormat wdata=new SimpleDateFormat("yyyy-MM-dd HH:mm");

        String data=wdata.format(new Date(lastModified()));
        String nazwa=getName();
        String rozmiar=Long.toString(length()/1024)+" kB";

        return (nazwa+" rozmiar: "+rozmiar+" last modified: "+data);
    }

    @Override
    public String toString()
    {
        return getName();
    }
}
