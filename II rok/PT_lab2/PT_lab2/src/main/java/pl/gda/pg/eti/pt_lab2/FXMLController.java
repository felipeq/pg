package pl.gda.pg.eti.pt_lab2;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.stage.DirectoryChooser;

public class FXMLController implements Initializable {

    @FXML
    private Label label;
    @FXML
    private TreeView<File> treeView;
    @FXML
    private Label label_top;
    @FXML
    private Button btnAddFile;

    @FXML
    public void dodajPlik(ActionEvent event) throws IOException {
        Button btn = (Button) event.getSource();

        TreeItem<File> selected = treeView.getSelectionModel().getSelectedItem();
        if (selected.getValue().isDirectory()) {
            selected = treeView.getSelectionModel().getSelectedItem();
        } else {
            selected = treeView.getSelectionModel().getSelectedItem().getParent();
        }
        String core;
        if (btn == btnAddFile) {
            core = "plik_";

        } else {
            core = "katalog_";

        }
        File nowy = new File(selected.getValue(), core + "1");
        while (nowy.exists()) {
            String nazwa = nowy.getName();
            nazwa = (nazwa.split("_")[1]);
            nowy = new File(selected.getValue(), core + (Integer.parseInt(nazwa) + 1));
        }
        if (btn == btnAddFile) {
            nowy.createNewFile();

        } else {
            nowy.mkdir();

        }

        selected.getChildren().add(new TreeItem<>(nowy));
        //}
    }

    void usunFile(TreeItem<File> file) {
        if (file.getValue().isDirectory()) {
            for (TreeItem<File> f : file.getChildren()) {
                usunFile(f);
            }
        }
        file.getParent().getChildren().remove(file);
        file.getValue().delete();
    }

    @FXML
    void usun(ActionEvent event) {
        TreeItem<File> selected = treeView.getSelectionModel().getSelectedItem();
        usunFile(selected);
    }

    @FXML
    public void btnFileChooserOnAction(ActionEvent event) {
        label.setText("OUGH");
        DirectoryChooser directoryChooser = new DirectoryChooser();
        directoryChooser.setTitle("Wybierz katalog");
        File plik = directoryChooser.showDialog(null);
        treeView.setCellFactory(new FileCellFactory());
        treeView.setShowRoot(false);
        treeView.setRoot(dodaj(plik));
        label_top.setText(treeView.getRoot().getValue().getAbsolutePath());

    }

    public TreeItem<File> dodaj(File file) {
        TreeItem<File> temp = new TreeItem<>(file);
        for (File f : file.listFiles()) {
            if (f.isDirectory()) {
                temp.getChildren().add(dodaj(f));
            } else {
                System.out.println(f.getName());
                temp.getChildren().add(new TreeItem<>(f));
            }
        }
        return temp;
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }

}
