/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.gda.pg.eti.pt_lab1;

import java.io.File;
import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Collection;
import java.util.Date;
import java.util.HashSet;
import java.util.TreeSet;

/**
 *
 * @author Filip
 */
enum Typ {

    PLIK, KATALOG
}

public final class DiskFile implements Comparable<DiskFile>, Serializable {

    private String name;
    private Typ typ;
    private Date lastModified;

    private final HashSet<DiskFile> hashSet = new HashSet<DiskFile>();
    private final TreeSet<DiskFile> treeSet = new TreeSet<DiskFile>();
    private Collection<DiskFile> kolekcja;

    @Override
    public int compareTo(DiskFile other) {
        if (this.typ.compareTo(other.typ) == 0) {
            if (this.name.compareToIgnoreCase(other.name) == 0) {
                if (this.lastModified.compareTo(other.lastModified) == 0) {
                    return 0;
                } else {
                    return (this.lastModified.compareTo(other.lastModified));
                }
            } else {
                return (this.name.compareToIgnoreCase(other.name));
            }
        } else {
            return (this.typ.compareTo(other.typ));
        }
    }

    public void setName(String a) {
        name = a;
    }

    public String getName() {
        return name;
    }

    public void setTyp(Typ x) {
        typ = x;
    }

    /**
     *
     * @return
     */
    public Typ getTyp() {
        return typ;
    }

    public void setLastModified(long x) {
        lastModified = new Date(x);
    }

    /**
     *
     * @param file
     * @param sorted 1=files will be sorted by name, 0 not
     */
    public DiskFile(File file, int sorted) {
        if (!file.exists()) {
            System.out.println("BŁĄD 001");
        }

        setName(file.getName());
        if (file.isFile()) {
            setTyp(Typ.PLIK);
        } else {
            setTyp(Typ.KATALOG);

            for (File f : file.listFiles()) {
                if (sorted == 0) {

                    hashSet.add(new DiskFile(f, sorted));
                } else {

                    treeSet.add(new DiskFile(f, sorted));
                }
            }
        }
        setLastModified(file.lastModified());
    }

    public String kreseczki(int deep) {
        StringBuilder wynik = new StringBuilder();
        deep++;
        for (int i = 0; i < deep; i++) {
            wynik.append("-");
        }
        return wynik.toString();
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 17 * hash + (this.name != null ? this.name.hashCode() : 0);
        hash = 17 * hash + (this.typ != null ? this.typ.hashCode() : 0);
        hash = 17 * hash + (this.lastModified != null ? this.lastModified.hashCode() : 0);
        hash = 17 * hash + (this.kolekcja != null ? this.kolekcja.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final DiskFile other = (DiskFile) obj;
        if ((this.name == null) ? (other.name != null) : !this.name.equals(other.name)) {
            return false;
        }
        if (this.typ != other.typ) {
            return false;
        }
        if (this.lastModified != other.lastModified && (this.lastModified == null || !this.lastModified.equals(other.lastModified))) {
            return false;
        }
        if (this.kolekcja != other.kolekcja && (this.kolekcja == null || !this.kolekcja.equals(other.kolekcja))) {
            return false;
        }
        return true;
    }

    public void show(int deep) {

        if (!treeSet.isEmpty()) {
            kolekcja = treeSet;
        } else {
            kolekcja = hashSet;
        }
        System.out.println(kreseczki(deep) + name + "\t" + typ + "\t" + FormatDate(lastModified));
        deep++;
        for (DiskFile i : kolekcja) {
            i.show(deep);
        }
    }

    public String FormatDate(Date date) {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String formattedDate = sdf.format(date);
        return (formattedDate);
    }
}
