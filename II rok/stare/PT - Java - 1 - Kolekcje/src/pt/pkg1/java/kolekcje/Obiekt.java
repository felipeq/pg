/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pt.pkg1.java.kolekcje;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

/**
 *
 * @author filip
 */
public class Obiekt implements Comparable<Obiekt> {

    private enum Typ {

        plik,
        katalog;
    };
    private String nazwa;
    private Typ typ;
    private Date data;
    private File plik;
    private Set<Obiekt> kolekcja;

    public void print(int poziom) // wyswietlenie zawartosci kolekcji
    {
        Iterator it = kolekcja.iterator();
        while (it.hasNext()) {
            FormatujWyjscie(poziom);
            Obiekt file = (Obiekt) it.next();
            System.out.println(file.Info());

            if (file.typ == Typ.katalog) {
                file.print(poziom + 1);
            }
        }
    }

    private void FormatujWyjscie(int poziom) {
        for (int i = 0; i < poziom; i++) {
            System.out.print("-");
        }
    }

    Obiekt(String path, boolean sort_us) {

        plik = new File(path);
        this.nazwa = plik.getName();
        this.data = new Date(plik.lastModified());
        CreateSet(sort_us);
        if (plik.isDirectory()) {
            typ = Typ.katalog;

        }
        if (plik.isFile()) {
            typ = Typ.plik;
        }
        if (plik.isFile() == false) {
            PrzegladajKatalog(sort_us);
        }

    }

    @Override
    public int compareTo(Obiekt obj) // porównanie obiektów
    {
        return nazwa.compareTo(obj.nazwa);
    }

    private void PrzegladajKatalog(boolean sort_us) {
        File zawartosc[] = plik.listFiles();
        for (int i = 0; i < zawartosc.length; i++) {
            kolekcja.add(new Obiekt(zawartosc[i].getAbsolutePath(), sort_us));
        }
        plik = null;
    }

    private void CreateSet(boolean sort_us) {
        if (sort_us == true) {
            kolekcja = new TreeSet<Obiekt>();
        }
        if (sort_us == false) {
            kolekcja = new HashSet<Obiekt>();
        }
    }

    public String Info() {
        String temp = nazwa + "";
        if (this.typ == Typ.katalog) {
            temp += "\tK\t";
        }
        if (this.typ == Typ.plik) {
            temp += "\tP\t";
        }
        temp += DateToString();
        return temp;
    }

    private String DateToString() {
        SimpleDateFormat temp = new SimpleDateFormat("yyyy-MM-dd");
        return temp.format(this.data);
    }
}
