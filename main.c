#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// --- C?u tr�c d? li?u BenhNhan ---
typedef struct {
    char ma[10];
    char ten[50];
    int tuoi;
    char sdt[15];
    char diaChi[100];
    char gioiTinh[10];
    char thoiGianDen[20]; // �?nh d?ng "YYYY-MM-DD HH:MM" ho?c "HH:MM DD/MM/YYYY"
    char trangThai[20]; // Tr?ng th�i (e.g., "Chua kham", "Da kham")
    char chanDoan[100]; // Th�m tru?ng ch?n do�n
    int uuTien; // M?c uu ti�n (1 = cao nh?t, 5 = th?p nh?t)
} BenhNhan;

// --- C?u tr�c Node cho Queue ---
typedef struct Node {
    BenhNhan data;
    struct Node *next;
} Node;

// --- C?u tr�c Queue (H�ng d?i) ---
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

// --- Bi?n to�n c?c d? qu?n l� danh s�ch b?nh nh�n v� Queue ---
BenhNhan danhSachTongHop[100]; // M?ng t?ng h?p t?t c? b?nh nh�n (d? ghi/d?c file v� t�m ki?m)
int soLuongTongHop = 0;

Queue qChuaKham; // H�ng d?i b?nh nh�n chua kh�m
Queue qDaKham;   // H�ng d?i b?nh nh�n d� kh�m

// --- Kh?i t?o Queue ---
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// --- Ki?m tra Queue r?ng ---
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// --- H�M TI?N �CH: HI?N TH? TH�NG TIN M?T B?NH NH�N ---
void hienThiBenhNhan(const BenhNhan* bn, bool chiTiet) {
    printf("M�(ID): %s     | H? t�n: %-20s | Tu?i: %-4d | Gi?i t�nh: %-8s\n", bn->ma, bn->ten, bn->tuoi, bn->gioiTinh);
    printf("�?a ch?: %-30s       | SDT: %-15s\n", bn->diaChi, bn->sdt);
    printf("Th?i gian d?n: %-18s     | Tr?ng th�i: %-12s | Uu ti�n: %-2d\n", bn->thoiGianDen, bn->trangThai, bn->uuTien);
    if (chiTiet && strlen(bn->chanDoan) > 0) {
        printf("Ch?n do�n: %s\n", bn->chanDoan);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
}

// --- H�M TI?N �CH: HI?N TH? DANH S�CH B?NH NH�N T?NG H?P ---
void hienThiDanhSachTongHop(const BenhNhan ds[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh s�ch b?nh nh�n tr?ng.\n");
        return;
    }
    printf("\n=== DANH S�CH T?NG H?P B?NH NH�N ===\n");
    printf("%-4s %-10s %-20s %-4s %-10s %-15s %-20s %-15s %-10s %-20s\n",
           "STT", "MaBN", "HoTen", "Tuoi", "GioiTinh", "SDT", "DiaChi", "ThoiGianDen", "TrangThai", "ChanDoan");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++) {
        printf("%-4d %-10s %-20s %-4d %-10s %-15s %-20s %-15s %-10s %-20s\n",
               i + 1,
               ds[i].ma,
               ds[i].ten,
               ds[i].tuoi,
               ds[i].gioiTinh,
               ds[i].sdt,
               ds[i].diaChi,
               ds[i].thoiGianDen,
               ds[i].trangThai,
               ds[i].chanDoan);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
}

// --- H�M LI�N QUAN �?N FILE ---
// Ghi danh s�ch b?nh nh�n v�o file (ghi d� file cu)
void ghiDanhSachVaoFile(const char *tenFile, const BenhNhan ds[], int soLuong) {
    FILE *f = fopen(tenFile, "w"); // M? ch? d? "w" d? ghi d�, kh�ng ph?i "a" (append)
    if (!f) {
        printf("Kh�ng th? m? file %s d? ghi.\n", tenFile);
        return;
    }

    for (int i = 0; i < soLuong; i++) {
        fprintf(f, "%s\n", ds[i].ma);
        fprintf(f, "%s\n", ds[i].ten);
        fprintf(f, "%d\n", ds[i].tuoi);
        fprintf(f, "%s\n", ds[i].gioiTinh);
        fprintf(f, "%s\n", ds[i].sdt);
        fprintf(f, "%s\n", ds[i].diaChi);
        fprintf(f, "%d\n", ds[i].uuTien); // Ghi th�m uu ti�n
        fprintf(f, "%s\n", ds[i].thoiGianDen);
        fprintf(f, "%s\n", ds[i].trangThai);
        fprintf(f, "%s\n", ds[i].chanDoan);
    }

    fclose(f);
    printf("�� ghi %d b?nh nh�n v�o file: %s\n", soLuong, tenFile);
}

// �?c danh s�ch b?nh nh�n t? file
int docDanhSachTuFile(const char *tenFile, BenhNhan ds[], int *soLuong) {
    FILE *f = fopen(tenFile, "r");
    if (!f) {
        // T?o d? li?u m?u n?u kh�ng c� file
        printf("Kh�ng th? m? file %s. T?o d? li?u m?u...\n", tenFile);
        strcpy(ds[0].ma, "BN001");
        strcpy(ds[0].ten, "Nguyen Van A");
        ds[0].tuoi = 25;
        strcpy(ds[0].gioiTinh, "Nam");
        strcpy(ds[0].sdt, "0123456789");
        strcpy(ds[0].diaChi, "Ha Noi");
        ds[0].uuTien = 2;
        strcpy(ds[0].thoiGianDen, "08:00 09/06/2025");
        strcpy(ds[0].trangThai, "Chua kham");
        strcpy(ds[0].chanDoan, "");
        
        strcpy(ds[1].ma, "BN002");
        strcpy(ds[1].ten, "Tran Thi B");
        ds[1].tuoi = 30;
        strcpy(ds[1].gioiTinh, "Nu");
        strcpy(ds[1].sdt, "0987654321");
        strcpy(ds[1].diaChi, "Ho Chi Minh");
        ds[1].uuTien = 1;
        strcpy(ds[1].thoiGianDen, "07:30 09/06/2025");
        strcpy(ds[1].trangThai, "Chua kham");
        strcpy(ds[1].chanDoan, "");
        
        strcpy(ds[2].ma, "BN003");
        strcpy(ds[2].ten, "Le Van C");
        ds[2].tuoi = 45;
        strcpy(ds[2].gioiTinh, "Nam");
        strcpy(ds[2].sdt, "0369852147");
        strcpy(ds[2].diaChi, "Da Nang");
        ds[2].uuTien = 3;
        strcpy(ds[2].thoiGianDen, "09:00 09/06/2025");
        strcpy(ds[2].trangThai, "Da kham");
        strcpy(ds[2].chanDoan, "Viem hong");
        
        *soLuong = 3;
        return 1;
    }

    *soLuong = 0;
    while (*soLuong < 100 &&
           fgets(ds[*soLuong].ma, sizeof(ds[*soLuong].ma), f) != NULL) {
        ds[*soLuong].ma[strcspn(ds[*soLuong].ma, "\n")] = '\0';

        if (fgets(ds[*soLuong].ten, sizeof(ds[*soLuong].ten), f) == NULL) break;
        ds[*soLuong].ten[strcspn(ds[*soLuong].ten, "\n")] = '\0';

        if (fscanf(f, "%d\n", &ds[*soLuong].tuoi) != 1) break;

        if (fgets(ds[*soLuong].gioiTinh, sizeof(ds[*soLuong].gioiTinh), f) == NULL) break;
        ds[*soLuong].gioiTinh[strcspn(ds[*soLuong].gioiTinh, "\n")] = '\0';

        if (fgets(ds[*soLuong].sdt, sizeof(ds[*soLuong].sdt), f) == NULL) break;
        ds[*soLuong].sdt[strcspn(ds[*soLuong].sdt, "\n")] = '\0';

        if (fgets(ds[*soLuong].diaChi, sizeof(ds[*soLuong].diaChi), f) == NULL) break;
        ds[*soLuong].diaChi[strcspn(ds[*soLuong].diaChi, "\n")] = '\0';

        if (fscanf(f, "%d\n", &ds[*soLuong].uuTien) != 1) break; // �?c uu ti�n

        if (fgets(ds[*soLuong].thoiGianDen, sizeof(ds[*soLuong].thoiGianDen), f) == NULL) break;
        ds[*soLuong].thoiGianDen[strcspn(ds[*soLuong].thoiGianDen, "\n")] = '\0';

        if (fgets(ds[*soLuong].trangThai, sizeof(ds[*soLuong].trangThai), f) == NULL) break;
        ds[*soLuong].trangThai[strcspn(ds[*soLuong].trangThai, "\n")] = '\0';

        if (fgets(ds[*soLuong].chanDoan, sizeof(ds[*soLuong].chanDoan), f) == NULL) break;
        ds[*soLuong].chanDoan[strcspn(ds[*soLuong].chanDoan, "\n")] = '\0';

        (*soLuong)++;
    }
    fclose(f);
    printf("�� d?c %d b?nh nh�n t? file: %s\n", *soLuong, tenFile);
    return 1;
}

// --- H�M QU?N L� ID B?NH NH�N ---
// Ki?m tra m� b?nh nh�n c� tr�ng kh�ng
bool kiemTraMaTrung(const char* ma) {
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].ma, ma) == 0) {
            return true; // M� d� t?n t?i
        }
    }
    return false; // M� chua t?n t?i
}

// T?o m?t m� ID b?nh nh�n ng?u nhi�n, duy nh?t.
bool taoMaBenhNhanTuDong(char* maBenhNhan) {
    int attempts = 0;
    srand(time(NULL)); // Kh?i t?o seed cho h�m rand()
    while (attempts < 1000) { // MAX_ATTEMPTS_GENERATE_ID = 1000
        int randomNumber = rand() % 999 + 1; // S? t? 001 d?n 999
        sprintf(maBenhNhan, "BN%03d", randomNumber);
        if (!kiemTraMaTrung(maBenhNhan)) {
            return true; // T�m th?y m� duy nh?t
        }
        attempts++;
    }
    printf("C?nh b�o: Kh�ng th? t?o m� b?nh nh�n duy nh?t. C� th? danh s�ch d� d?y ho?c xung d?t.\n");
    return false; // Kh�ng t?o du?c m�
}

// --- H�M NH?P D? LI?U B?NH NH�N ---
void nhapMotBenhNhan(BenhNhan* bn) {
    if (soLuongTongHop >= 100) { // MAX_BENHNHAN = 100
        printf("Danh s�ch b?nh nh�n d� d?y!\n");
        return;
    }

    // T? d?ng t?o m� duy nh?t ID
    if (!taoMaBenhNhanTuDong(bn->ma)) {
        printf("L?i: Kh�ng th? t?o m�. Vui l�ng ki?m tra l?i.\n");
        return;
    }
    printf("M� b?nh nh�n t? d?ng t?o: %s\n", bn->ma);

    printf("H? t�n: ");
    fflush(stdin); // X�a b? d?m b�n ph�m tr�n Windows
    fgets(bn->ten, sizeof(bn->ten), stdin);
    bn->ten[strcspn(bn->ten, "\n")] = 0;

    printf("Tu?i: ");
    scanf("%d", &bn->tuoi);

    printf("Gi?i t�nh: ");
    scanf("%s", bn->gioiTinh);

    printf("S? di?n tho?i: ");
    scanf("%s", bn->sdt);

    printf("�?a ch?: ");
    fflush(stdin);
    fgets(bn->diaChi, sizeof(bn->diaChi), stdin);
    bn->diaChi[strcspn(bn->diaChi, "\n")] = 0;

    printf("M?c uu ti�n (1-C?p c?u, 2-Kh?n c?p, 3-B�nh thu?ng, 4-T�i kh�m, 5-Th?p): ");
    scanf("%d", &bn->uuTien);
    while (bn->uuTien < 1 || bn->uuTien > 5) {
        printf("M?c uu ti�n kh�ng h?p l?. Vui l�ng nh?p t? 1 d?n 5: ");
        scanf("%d", &bn->uuTien);
    }

    // L?y th?i gian hi?n t?i
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(bn->thoiGianDen, sizeof(bn->thoiGianDen), "%H:%M %d/%m/%Y", info);

    strcpy(bn->trangThai, "Chua kham"); // Tr?ng th�i m?c d?nh
    strcpy(bn->chanDoan, ""); // Ch?n do�n m?c d?nh r?ng

    printf("\n�� th�m b?nh nh�n: %s (M�: %s)\n", bn->ten, bn->ma);
}

// Nh?p nhi?u b?nh nh�n
void nhapNhieuBenhNhan() {
    int soLuongCanNhap;
    printf("Nh?p s? lu?ng b?nh nh�n mu?n th�m: ");
    scanf("%d", &soLuongCanNhap);

    if (soLuongTongHop + soLuongCanNhap > 100) {
        printf("Kh�ng th? th�m %d b?nh nh�n. Vu?t qu� s? lu?ng t?i da (%d).\n", soLuongCanNhap, 100);
        return;
    }

    for (int i = 0; i < soLuongCanNhap; i++) {
        printf("\n--- Nh?p th�ng tin b?nh nh�n th? %d ---\n", i + 1);
        nhapMotBenhNhan(&danhSachTongHop[soLuongTongHop]);
        soLuongTongHop++;
    }
    printf("\n�� th�m %d b?nh nh�n m?i v�o danh s�ch t?ng h?p.\n", soLuongCanNhap);
}

// --- H�M S?P X?P DANH S�CH CH? KH�M ---
// H�m so s�nh d? s?p x?p: Uu ti�n cao tru?c, n?u b?ng th� th?i gian d?n tru?c
bool soSanhBenhNhan(const BenhNhan* a, const BenhNhan* b) {
    if (a->uuTien != b->uuTien) {
        return a->uuTien < b->uuTien; // Uu ti�n th?p hon (s? nh? hon) c� nghia l� quan tr?ng hon
    }
    return strcmp(a->thoiGianDen, b->thoiGianDen) < 0;
}

// S?p x?p b?ng Selection Sort
void selectionSort(BenhNhan ds[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (soSanhBenhNhan(&ds[j], &ds[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            BenhNhan temp = ds[i];
            ds[i] = ds[minIndex];
            ds[minIndex] = temp;
        }
    }
}

// S?p x?p b?ng Insertion Sort
void insertionSort(BenhNhan ds[], int n) {
    for (int i = 1; i < n; i++) {
        BenhNhan key = ds[i];
        int j = i - 1;
        while (j >= 0 && soSanhBenhNhan(&key, &ds[j])) {
            ds[j + 1] = ds[j];
            j--;
        }
        ds[j + 1] = key;
    }
}

// H�m s?p x?p ch�nh (c� th? ch?n thu?t to�n)
void sapXepDanhSachCho(BenhNhan ds[], int soLuong, int thuatToan) {
    printf("�ang s?p x?p danh s�ch ch? kh�m...\n");
    if (thuatToan == 1) {
        printf("S? d?ng Selection Sort\n");
        selectionSort(ds, soLuong);
    } else {
        printf("S? d?ng Insertion Sort\n");
        insertionSort(ds, soLuong);
    }
    printf("S?p x?p ho�n t?t!\n");
}

// --- H�M T�M KI?M B?NH NH�N ---
// T�m ki?m b?nh nh�n theo m�
void timBenhNhanTheoMa(const char* maCanTim) {
    bool found = false;
    printf("\n--- K?t qu? t�m ki?m b?nh nh�n theo m� '%s' ---\n", maCanTim);
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].ma, maCanTim) == 0) {
            hienThiBenhNhan(&danhSachTongHop[i], true);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Kh�ng t�m th?y b?nh nh�n v?i m� '%s'.\n", maCanTim);
    }
}

// T�m ki?m b?nh nh�n theo t�n
void timBenhNhanTheoTen(const char* tenCanTim) {
    int countFound = 0;
    printf("\n--- K?t qu? t�m ki?m b?nh nh�n theo t�n '%s' ---\n", tenCanTim);
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strstr(danhSachTongHop[i].ten, tenCanTim) != NULL) {
            hienThiBenhNhan(&danhSachTongHop[i], true);
            countFound++;
        }
    }
    if (countFound > 0) {
        printf("-> T�m th?y %d b?nh nh�n v?i t�n '%s'.\n", countFound, tenCanTim);
    } else {
        printf("Kh�ng t�m th?y b?nh nh�n v?i t�n '%s'.\n", tenCanTim);
    }
}

// --- H�M C?P NH?T TR?NG TH�I B?NH NH�N ---
bool capNhatTrangThaiTheoMa(const char* maBN, const char* trangThaiMoi, const char* chanDoanMoi) {
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].ma, maBN) == 0) {
            strcpy(danhSachTongHop[i].trangThai, trangThaiMoi);
            strcpy(danhSachTongHop[i].chanDoan, chanDoanMoi);
            printf("�� c?p nh?t tr?ng th�i b?nh nh�n %s th�nh: %s\n", maBN, trangThaiMoi);
            return true;
        }
    }
    printf("Kh�ng t�m th?y b?nh nh�n c� m�: %s\n", maBN);
    return false;
}

// --- MENU QU?N L� H�NG �?I KH�M ---
// �ua b?nh nh�n t? m?ng v�o Queue
void duaMangVaoQueue(Queue *q, BenhNhan ds[], int soLuong) {
    for (int i = 0; i < soLuong; i++) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Kh�ng th? c?p ph�t b? nh? cho node m?i.\n");
            return;
        }
        newNode->data = ds[i];
        newNode->next = NULL;

        if (q->rear == NULL) {
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }
}

// L?y b?nh nh�n d?u ti�n t? h�ng d?i ch? kh�m v� chuy?n sang h�ng d?i d� kh�m
int LayBenhNhanDau(Queue *qChuaKham, Queue *qDaKham) {
    if (isEmpty(qChuaKham)) {
        printf("H�ng d?i b?nh nh�n ch? kh�m r?ng.\n");
        return 0;
    }

    Node *p = qChuaKham->front;

    if (strcmp(p->data.trangThai, "Chua kham") == 0) {
        printf("\nB?nh nh�n dang du?c g?i kh�m:\n");
        hienThiBenhNhan(&p->data, false);

        strcpy(p->data.trangThai, "Da kham");
        printf("Nh?p ch?n do�n cho b?nh nh�n %s: ", p->data.ten);
        fflush(stdin);
        fgets(p->data.chanDoan, sizeof(p->data.chanDoan), stdin);
        p->data.chanDoan[strcspn(p->data.chanDoan, "\n")] = '\0';

        printf("B?nh nh�n %s d� du?c c?p nh?t tr?ng th�i v� ch?n do�n.\n", p->data.ten);

        // Chuy?n b?nh nh�n t? qChuaKham sang qDaKham
        qChuaKham->front = p->next;
        if (qChuaKham->front == NULL) {
            qChuaKham->rear = NULL;
        }

        p->next = NULL;
        if (qDaKham->rear == NULL) {
            qDaKham->front = qDaKham->rear = p;
        } else {
            qDaKham->rear->next = p;
            qDaKham->rear = p;
        }
        
        // C?p nh?t v�o danh s�ch t?ng h?p
        for (int i = 0; i < soLuongTongHop; i++) {
            if (strcmp(danhSachTongHop[i].ma, p->data.ma) == 0) {
                strcpy(danhSachTongHop[i].trangThai, "Da kham");
                strcpy(danhSachTongHop[i].chanDoan, p->data.chanDoan);
                break;
            }
        }
        
        return 1;
    } else {
        printf("B?nh nh�n d?u ti�n trong h�ng d?i d� du?c kh�m.\n");
        return 0;
    }
}

// Hi?n th? b?nh nh�n trong m?t Queue
void hienThiQueue(Queue *q, const char* tenQueue) {
    if (isEmpty(q)) {
        printf("Danh s�ch %s r?ng.\n", tenQueue);
        return;
    }

    printf("\n=== DANH S�CH B?NH NH�N TRONG %s ===\n", tenQueue);
    printf("%-4s %-10s %-20s %-4s %-10s %-15s %-15s %-10s %-20s\n",
           "STT", "MaBN", "HoTen", "Tuoi", "GioiTinh", "SDT", "ThoiGianDen", "TrangThai", "ChanDoan");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    Node *p = q->front;
    int stt = 1;
    while (p != NULL) {
        printf("%-4d %-10s %-20s %-4d %-10s %-15s %-15s %-10s %-20s\n",
               stt++,
               p->data.ma,
               p->data.ten,
               p->data.tuoi,
               p->data.gioiTinh,
               p->data.sdt,
               p->data.thoiGianDen,
               p->data.trangThai,
               p->data.chanDoan);
        p = p->next;
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");
}

// Chuy?n Queue sang m?ng
int chuyenQueueSangMang(Queue *q, BenhNhan ds[]) {
    int i = 0;
    Node *p = q->front;
    while (p != NULL) {
        ds[i++] = p->data;
        p = p->next;
    }
    return i;
}

// Gi?i ph�ng b? nh? c?a Queue
void freeQueue(Queue *q) {
    Node *current = q->front;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

// --- MENU CH�NH C?A CHUONG TR�NH ---
void menuChinh() {
    int luaChon;
    char maCanTim[10];
    char tenCanTim[50];
    int soLuongQCK = 0;
    int soLuongQDK = 0;
    BenhNhan tempDSQCK[100];
    BenhNhan tempDSQDK[100];

    // Kh?i t?o c�c Queue
    initQueue(&qChuaKham);
    initQueue(&qDaKham);

    // �?c d? li?u t? file khi kh?i d?ng chuong tr�nh
    docDanhSachTuFile("benhnhan_tonghop.txt", danhSachTongHop, &soLuongTongHop);

    // Ph�n lo?i b?nh nh�n v�o 2 h�ng d?i
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].trangThai, "Chua kham") == 0) {
            tempDSQCK[soLuongQCK++] = danhSachTongHop[i];
        } else if (strcmp(danhSachTongHop[i].trangThai, "Da kham") == 0) {
            tempDSQDK[soLuongQDK++] = danhSachTongHop[i];
        }
    }

    // S?p x?p danh s�ch ch? kh�m theo uu ti�n
    sapXepDanhSachCho(tempDSQCK, soLuongQCK, 1); // S? d?ng Selection Sort

    // �ua v�o Queue
    duaMangVaoQueue(&qChuaKham, tempDSQCK, soLuongQCK);
    duaMangVaoQueue(&qDaKham, tempDSQDK, soLuongQDK);

    do {
        printf("\n========== H? TH?NG QU?N L� KH�M B?NH ==========\n");
        printf("1. Th�m b?nh nh�n m?i\n");
        printf("2. Hi?n th? danh s�ch ch? kh�m\n");
        printf("3. Hi?n th? danh s�ch d� kh�m\n");
        printf("4. G?i b?nh nh�n ti?p theo\n");
        printf("5. T�m ki?m b?nh nh�n theo m�\n");
        printf("6. T�m ki?m b?nh nh�n theo t�n\n");
        printf("7. Hi?n th? danh s�ch t?ng h?p\n");
        printf("8. S?p x?p l?i danh s�ch ch? kh�m\n");
        printf("9. Luu d? li?u v� tho�t\n");
        printf("================================================\n");
        printf("Nh?p l?a ch?n: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                printf("\n--- TH�M B?NH NH�N M?I ---\n");
                nhapMotBenhNhan(&danhSachTongHop[soLuongTongHop]);
                
                // Th�m v�o queue ch? kh�m
                Node *newNode = (Node *)malloc(sizeof(Node));
                if (newNode != NULL) {
                    newNode->data = danhSachTongHop[soLuongTongHop];
                    newNode->next = NULL;
                    
                    if (qChuaKham.rear == NULL) {
                        qChuaKham.front = qChuaKham.rear = newNode;
                    } else {
                        qChuaKham.rear->next = newNode;
                        qChuaKham.rear = newNode;
                    }
                    soLuongTongHop++;
                    printf("�� th�m b?nh nh�n v�o h�ng d?i ch? kh�m.\n");
                }
                break;
                
            case 2:
                printf("\n--- DANH S�CH CH? KH�M ---\n");
                hienThiQueue(&qChuaKham, "H�NG �?I CH? KH�M");
                break;
                
            case 3:
                printf("\n--- DANH S�CH �� KH�M ---\n");
                hienThiQueue(&qDaKham, "H�NG �?I �� KH�M");
                break;
                
            case 4:
                printf("\n--- G?I B?NH NH�N TI?P THEO ---\n");
                LayBenhNhanDau(&qChuaKham, &qDaKham);
                break;
                
            case 5:
                printf("\n--- T�M KI?M THEO M� ---\n");
                printf("Nh?p m� b?nh nh�n c?n t�m: ");
                scanf("%s", maCanTim);
                timBenhNhanTheoMa(maCanTim);
                break;
                
            case 6:
                printf("\n--- T�M KI?M THEO T�N ---\n");
                printf("Nh?p t�n b?nh nh�n c?n t�m: ");
                fflush(stdin);
                fgets(tenCanTim, sizeof(tenCanTim), stdin);
                tenCanTim[strcspn(tenCanTim, "\n")] = '\0';
                timBenhNhanTheoTen(tenCanTim);
                break;
                
            case 7:
                printf("\n--- DANH S�CH T?NG H?P ---\n");
                hienThiDanhSachTongHop(danhSachTongHop, soLuongTongHop);
                break;
                
            case 8:
                printf("\n--- S?P X?P L?I DANH S�CH CH? KH�M ---\n");
                soLuongQCK = chuyenQueueSangMang(&qChuaKham, tempDSQCK);
                freeQueue(&qChuaKham);
                initQueue(&qChuaKham);
                
                printf("Ch?n thu?t to�n s?p x?p (1-Selection Sort, 2-Insertion Sort): ");
                int thuatToan;
                scanf("%d", &thuatToan);
                sapXepDanhSachCho(tempDSQCK, soLuongQCK, thuatToan);
                duaMangVaoQueue(&qChuaKham, tempDSQCK, soLuongQCK);
                printf("�� s?p x?p l?i danh s�ch ch? kh�m.\n");
                break;
                
            case 9:
                printf("\n--- LUU D? LI?U V� THO�T ---\n");
                ghiDanhSachVaoFile("benhnhan_tonghop.txt", danhSachTongHop, soLuongTongHop);
                
                soLuongQCK = chuyenQueueSangMang(&qChuaKham, tempDSQCK);
                ghiDanhSachVaoFile("benhnhan_chuakham.txt", tempDSQCK, soLuongQCK);
                
                soLuongQDK = chuyenQueueSangMang(&qDaKham, tempDSQDK);
                ghiDanhSachVaoFile("benhnhan_dakham.txt", tempDSQDK, soLuongQDK);
                
                printf("�� luu d? li?u th�nh c�ng!\n");
                break;
                
            default:
                printf("L?a ch?n kh�ng h?p l?!\n");
                break;
        }
    } while (luaChon != 9);

    // Gi?i ph�ng b? nh?
    freeQueue(&qChuaKham);
    freeQueue(&qDaKham);
    
    printf("C?m on b?n d� s? d?ng h? th?ng!\n");
}

// --- H�M MAIN ---
int main() {
    menuChinh();
    return 0;
}
