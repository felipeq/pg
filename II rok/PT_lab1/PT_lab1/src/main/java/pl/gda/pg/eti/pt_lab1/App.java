package pl.gda.pg.eti.pt_lab1;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * Hello world!
 *
 */
public class App {

    public static void main(String[] args) throws Exception {
        int SORTED = 0;
        String root_path = "foldery";
        //DiskFile root = Deserialize("serialized.dat");
        DiskFile root = new DiskFile(new File(root_path), SORTED);
        root.show(0);
        Serializuj(root, "serialized.dat");
    }

    public static DiskFile Deserialize(String path) throws IOException, ClassNotFoundException {
        ObjectInputStream in = new ObjectInputStream(
                new BufferedInputStream(
                        new FileInputStream(path)));
        DiskFile x = (DiskFile) in.readObject();
        return x;
    }

    public static void Serializuj(DiskFile x, String path) throws IOException {
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(path));
        oos.writeObject(x);
        oos.close();
    }
}
