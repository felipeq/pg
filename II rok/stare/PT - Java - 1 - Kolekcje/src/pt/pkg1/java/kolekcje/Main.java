/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pt.pkg1.java.kolekcje;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 *
 * @author filip
 */
public class Main {

    public static void main(String[] args) {
        SimpleDateFormat temp = new SimpleDateFormat("yyyy-MM-dd");
        boolean sort_us = true;
        if (args.length > 1) {
            if ("0".equals(args[1])) {
                sort_us = false;
            }
        }
        File root = new File(args[0]);
        Date data;
        data = new Date(root.lastModified());
        Obiekt obiekt = new Obiekt(args[0], sort_us);
        System.out.println(root.getName() + "\tK\t" + temp.format(data));
        obiekt.print(1);
    }
}
