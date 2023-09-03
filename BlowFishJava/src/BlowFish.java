import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.Key;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class BlowFish {

    private static final String ALGORITHM = "Blowfish";
    private static String key;
    private static final String SAMPLE_FILE_PATH =
            "C:\\Users\\Genco\\PycharmProjects\\pythonProject1\\binary-output.txt";
    private static final String ENCRYPTED_FILE_PATH =
            "C:\\Users\\Genco\\PycharmProjects\\pythonProject1\\Encrypt.txt";
    private static final String DECRYPTED_FILE_PATH =
            "C:\\Users\\Genco\\PycharmProjects\\pythonProject1\\Decrypt.txt";
    private static final String KEY_FILE_PATH =
            "C:\\Users\\Genco\\PycharmProjects\\pythonProject1\\key.txt";

    public static void main(String[] args) {

        File sampleFile = new File(SAMPLE_FILE_PATH);
        File encryptedFile = new File(ENCRYPTED_FILE_PATH);
        File decryptedFile = new File(DECRYPTED_FILE_PATH);
        try{
            File keyFile = new File(KEY_FILE_PATH);
            Scanner sc = new Scanner(keyFile);
            while(sc.hasNextLine()){
            key =sc.nextLine();
            }
        sc.close();
        } catch(FileNotFoundException e){
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        
        
        try {
            BlowFish.encrypt(sampleFile, encryptedFile);
            BlowFish.decrypt(encryptedFile, decryptedFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void encrypt(File sampleFile, File outputFile)
            throws Exception {
        doCrypto(Cipher.ENCRYPT_MODE, sampleFile, outputFile);

    }

    public static void decrypt(File sampleFile, File outputFile)
            throws Exception {
        doCrypto(Cipher.DECRYPT_MODE, sampleFile, outputFile);

    }

    private static void doCrypto(int cipherMode, File sampleFile,
                                 File outputFile) throws Exception {

        Key secretKey = new SecretKeySpec(key.getBytes(), ALGORITHM);
        Cipher cipher = Cipher.getInstance(ALGORITHM);
        cipher.init(cipherMode, secretKey);

        InputStream inputStream = new FileInputStream(sampleFile);
        byte[] inputBytes = new byte[(int) sampleFile.length()];
        inputStream.read(inputBytes);

        byte[] outputBytes = cipher.doFinal(inputBytes);

        OutputStream outputStream = new FileOutputStream(outputFile);
        outputStream.write(outputBytes);

        inputStream.close();
        outputStream.close();

    }
}