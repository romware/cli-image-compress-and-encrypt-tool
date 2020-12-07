# cli-image-compress-and-encrypt-tool

![version](https://img.shields.io/badge/version-1.0.0-blue)

**Sizey McSizeface** is an image compression and encryption application with unique CLI inline previews.


# Objective
The objective of this project is to create a program which enables multiple unique users to be provided with a secure environment where they can store encrypted images that only they can access. These imported images can then be exported as bitmap files which are readable by the operating system. Within this export process, images are decrypted with their encryption key, compressed to a reduced file size and optionally applied with selected colour or brightness filter.

Furthermore, the program includes an administrator account with extra privileges including the ability to create new user accounts. Both the administrator and standard users have their user data and images stored in individually encrypted binary files, automatically preloaded upon the running of the program.


# Scope
The primary features of this program are built upon the BMP file format. Features such as importing, exporting, compressing, encrypting, decrypting and applying filters all depend upon this format in order to read and write the necessary data they require in a uniform and standardised structure. Therefore, the BMP file type with 16 and 32-bit colour standards were selected as the required file types for importing images.

Encryption is performed using strings of characters to encrypt the images that are imported. Each colour element of each pixel is enciphered according to the secret key which the user has entered, making the encrypted image lose all original shapes and features, thus uninterpretable unless decrypted with the correct key.

Compression is performed using a lossy compression technique where the number of pixels are reduced by averaging the colours of several pixels down to one, thus reducing both the file size and image resolution whilst maintaining the original aspect ratio.

Storage is utilised by generating user specific binary files to keep the encrypted images and user data in a structured and secure environment. Access to the encrypted bitmaps in the binary file databases are protected by passwords created by their respective user.

The program will initialise by requesting the user to login, followed by a menu display with several options includes adding users (admin only), viewing images, importing images, deleting images, exporting images and logging out. The options to compress, decrypt and filter images are available under the export feature. Different users will experience a different file list which they can utilise these options depending on separate access to their database.


# Structured Analysis and Interdependencies
![Structure](/img/structure.png)


# Getting Started Guide
Upon downloading all submitted source files, open terminal in the source files directory.
```sh
cd directory/where/files/were/downloaded
```
Execute make file to compile the program 
```sh
make sizeymcsizeface
```
Run the newly compiled file
```sh
./sizemcsizeface
```
Enter the administrator login credentials
* Username: “admin”
* Password: “password123”

# Preview

Original Image

![Structure](/img/original.png)

Encrypted Image

![Structure](/img/encrypted.png)

Incorrect Key Image

![Structure](/img/incorrect.png)

Terminal Preview

![Structure](/img/terminal.png)
