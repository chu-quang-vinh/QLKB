#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// --- Cau truc du lieu BenhNhan ---
typedef struct {
    char maBenhNhan[10];
    char hoTen[50];
    char gioiTinh[10];
    char ngaySinh[15]; // Dinh dang "DD/MM/YYYY"
    char canCuocCongDan[15];
    char hoKhauThuongTru[100];
    char soDienThoai[15];
    char thoiGianDen[20]; // Dinh dang "HH:MM DD/MM/YYYY"
    char mucDoUuTien[20]; // "Cap cuu", "Thong thuong", "Tai kham"
    char trangThai[20]; // "Cho kham", "Dang kham", "Hoan thanh"
    char chanDoan[100]; // Them truong chan doan
} BenhNhan;

// --- Cau truc Node cho Queue ---
typedef struct Node {
    BenhNhan data;
    struct Node *next;
} Node;

// --- Cau truc Queue (Hang doi) ---
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

// --- Bien toan cuc de quan ly danh sach benh nhan va Queue ---
BenhNhan danhSachTongHop[100]; // Mang tong hop tat ca benh nhan
int soLuongTongHop = 0;

Queue qChoKham; // Hang doi benh nhan cho kham
Queue qDangKham; // Hang doi benh nhan dang kham
Queue qHoanThanh; // Hang doi benh nhan hoan thanh

// --- Khoi tao Queue ---
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// --- Kiem tra Queue rong ---
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// --- HAM TIEN ICH: HIEN THI THONG TIN MOT BENH NHAN ---
void hienThiBenhNhan(const BenhNhan* bn, bool chiTiet) {
    printf("Ma BN: %s | Ho ten: %-20s | Gioi tinh: %-5s | Ngay sinh: %-12s\n", 
           bn->maBenhNhan, bn->hoTen, bn->gioiTinh, bn->ngaySinh);
    printf("CCCD: %-15s | SDT: %-15s\n", bn->canCuocCongDan, bn->soDienThoai);
    printf("Ho khau: %-50s\n", bn->hoKhauThuongTru);
    printf("Thoi gian den: %-18s | Uu tien: %-15s | Trang thai: %-12s\n", 
           bn->thoiGianDen, bn->mucDoUuTien, bn->trangThai);
    if (chiTiet && strlen(bn->chanDoan) > 0) {
        printf("Chan doan: %s\n", bn->chanDoan);
    }
    printf("----------------------------------------------------------------------------------------------------------------\n");
}

// --- HAM TIEN ICH: HIEN THI DANH SACH BENH NHAN TONG HOP ---
void hienThiDanhSachTongHop(const BenhNhan ds[], int soLuong) {
    if (soLuong == 0) {
        printf("Danh sach benh nhan trong.\n");
        return;
    }
    printf("\n=== DANH SACH TONG HOP BENH NHAN ===\n");
    printf("%-4s %-10s %-20s %-8s %-12s %-15s %-15s %-15s %-12s %-20s\n",
           "STT", "MaBN", "HoTen", "GioiTinh", "NgaySinh", "CCCD", "SDT", "UuTien", "TrangThai", "ChanDoan");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++) {
        printf("%-4d %-10s %-20s %-8s %-12s %-15s %-15s %-15s %-12s %-20s\n",
               i + 1,
               ds[i].maBenhNhan,
               ds[i].hoTen,
               ds[i].gioiTinh,
               ds[i].ngaySinh,
               ds[i].canCuocCongDan,
               ds[i].soDienThoai,
               ds[i].mucDoUuTien,
               ds[i].trangThai,
               ds[i].chanDoan);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
}

// --- HAM LIEN QUAN DEN FILE ---
// Ghi danh sach benh nhan vao file
void ghiDanhSachVaoFile(const char *tenFile, const BenhNhan ds[], int soLuong) {
    FILE *f = fopen(tenFile, "w");
    if (!f) {
        printf("Khong the mo file %s de ghi.\n", tenFile);
        return;
    }

    for (int i = 0; i < soLuong; i++) {
        fprintf(f, "%s\n", ds[i].maBenhNhan);
        fprintf(f, "%s\n", ds[i].hoTen);
        fprintf(f, "%s\n", ds[i].gioiTinh);
        fprintf(f, "%s\n", ds[i].ngaySinh);
        fprintf(f, "%s\n", ds[i].canCuocCongDan);
        fprintf(f, "%s\n", ds[i].hoKhauThuongTru);
        fprintf(f, "%s\n", ds[i].soDienThoai);
        fprintf(f, "%s\n", ds[i].thoiGianDen);
        fprintf(f, "%s\n", ds[i].mucDoUuTien);
        fprintf(f, "%s\n", ds[i].trangThai);
        fprintf(f, "%s\n", ds[i].chanDoan);
    }

    fclose(f);
    printf("Da ghi %d benh nhan vao file: %s\n", soLuong, tenFile);
}

// Doc danh sach benh nhan tu file
int docDanhSachTuFile(const char *tenFile, BenhNhan ds[], int *soLuong) {
    FILE *f = fopen(tenFile, "r");
    if (!f) {
        printf("Khong the mo file %s. Tao du lieu mau...\n", tenFile);
        // Tao du lieu mau
        strcpy(ds[0].maBenhNhan, "BN001");
        strcpy(ds[0].hoTen, "Nguyen Van A");
        strcpy(ds[0].gioiTinh, "Nam");
        strcpy(ds[0].ngaySinh, "15/05/1990");
        strcpy(ds[0].canCuocCongDan, "123456789012");
        strcpy(ds[0].hoKhauThuongTru, "123 Nguyen Trai, Ha Noi");
        strcpy(ds[0].soDienThoai, "0123456789");
        strcpy(ds[0].thoiGianDen, "08:00 11/06/2025");
        strcpy(ds[0].mucDoUuTien, "Cap cuu");
        strcpy(ds[0].trangThai, "Cho kham");
        strcpy(ds[0].chanDoan, "");
        
        strcpy(ds[1].maBenhNhan, "BN002");
        strcpy(ds[1].hoTen, "Tran Thi B");
        strcpy(ds[1].gioiTinh, "Nu");
        strcpy(ds[1].ngaySinh, "20/03/1985");
        strcpy(ds[1].canCuocCongDan, "987654321098");
        strcpy(ds[1].hoKhauThuongTru, "456 Le Loi, Ho Chi Minh");
        strcpy(ds[1].soDienThoai, "0987654321");
        strcpy(ds[1].thoiGianDen, "07:30 11/06/2025");
        strcpy(ds[1].mucDoUuTien, "Thong thuong");
        strcpy(ds[1].trangThai, "Cho kham");
        strcpy(ds[1].chanDoan, "");
        
        strcpy(ds[2].maBenhNhan, "BN003");
        strcpy(ds[2].hoTen, "Le Van C");
        strcpy(ds[2].gioiTinh, "Nam");
        strcpy(ds[2].ngaySinh, "10/12/1975");
        strcpy(ds[2].canCuocCongDan, "456789123456");
        strcpy(ds[2].hoKhauThuongTru, "789 Tran Phu, Da Nang");
        strcpy(ds[2].soDienThoai, "0369852147");
        strcpy(ds[2].thoiGianDen, "09:00 11/06/2025");
        strcpy(ds[2].mucDoUuTien, "Tai kham");
        strcpy(ds[2].trangThai, "Hoan thanh");
        strcpy(ds[2].chanDoan, "Viem hong");
        
        *soLuong = 3;
        return 1;
    }

    *soLuong = 0;
    while (*soLuong < 100) {
        if (fgets(ds[*soLuong].maBenhNhan, sizeof(ds[*soLuong].maBenhNhan), f) == NULL) break;
        ds[*soLuong].maBenhNhan[strcspn(ds[*soLuong].maBenhNhan, "\n")] = '\0';

        if (fgets(ds[*soLuong].hoTen, sizeof(ds[*soLuong].hoTen), f) == NULL) break;
        ds[*soLuong].hoTen[strcspn(ds[*soLuong].hoTen, "\n")] = '\0';

        if (fgets(ds[*soLuong].gioiTinh, sizeof(ds[*soLuong].gioiTinh), f) == NULL) break;
        ds[*soLuong].gioiTinh[strcspn(ds[*soLuong].gioiTinh, "\n")] = '\0';

        if (fgets(ds[*soLuong].ngaySinh, sizeof(ds[*soLuong].ngaySinh), f) == NULL) break;
        ds[*soLuong].ngaySinh[strcspn(ds[*soLuong].ngaySinh, "\n")] = '\0';

        if (fgets(ds[*soLuong].canCuocCongDan, sizeof(ds[*soLuong].canCuocCongDan), f) == NULL) break;
        ds[*soLuong].canCuocCongDan[strcspn(ds[*soLuong].canCuocCongDan, "\n")] = '\0';

        if (fgets(ds[*soLuong].hoKhauThuongTru, sizeof(ds[*soLuong].hoKhauThuongTru), f) == NULL) break;
        ds[*soLuong].hoKhauThuongTru[strcspn(ds[*soLuong].hoKhauThuongTru, "\n")] = '\0';

        if (fgets(ds[*soLuong].soDienThoai, sizeof(ds[*soLuong].soDienThoai), f) == NULL) break;
        ds[*soLuong].soDienThoai[strcspn(ds[*soLuong].soDienThoai, "\n")] = '\0';

        if (fgets(ds[*soLuong].thoiGianDen, sizeof(ds[*soLuong].thoiGianDen), f) == NULL) break;
        ds[*soLuong].thoiGianDen[strcspn(ds[*soLuong].thoiGianDen, "\n")] = '\0';

        if (fgets(ds[*soLuong].mucDoUuTien, sizeof(ds[*soLuong].mucDoUuTien), f) == NULL) break;
        ds[*soLuong].mucDoUuTien[strcspn(ds[*soLuong].mucDoUuTien, "\n")] = '\0';

        if (fgets(ds[*soLuong].trangThai, sizeof(ds[*soLuong].trangThai), f) == NULL) break;
        ds[*soLuong].trangThai[strcspn(ds[*soLuong].trangThai, "\n")] = '\0';

        if (fgets(ds[*soLuong].chanDoan, sizeof(ds[*soLuong].chanDoan), f) == NULL) break;
        ds[*soLuong].chanDoan[strcspn(ds[*soLuong].chanDoan, "\n")] = '\0';

        (*soLuong)++;
    }
    fclose(f);
    printf("Da doc %d benh nhan tu file: %s\n", *soLuong, tenFile);
    return 1;
}

// --- HAM QUAN LY ID BENH NHAN ---
bool kiemTraMaTrung(const char* ma) {
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].maBenhNhan, ma) == 0) {
            return true;
        }
    }
    return false;
}

bool taoMaBenhNhanTuDong(char* maBenhNhan) {
    int attempts = 0;
    srand(time(NULL));
    while (attempts < 1000) {
        int randomNumber = rand() % 999 + 1;
        sprintf(maBenhNhan, "BN%03d", randomNumber);
        if (!kiemTraMaTrung(maBenhNhan)) {
            return true;
        }
        attempts++;
    }
    printf("Canh bao: Khong the tao ma benh nhan duy nhat.\n");
    return false;
}

// --- HAM NHAP DU LIEU BENH NHAN ---
void nhapMotBenhNhan(BenhNhan* bn) {
    if (soLuongTongHop >= 100) {
        printf("Danh sach benh nhan da day!\n");
        return;
    }

    // Tu dong tao ma duy nhat
    if (!taoMaBenhNhanTuDong(bn->maBenhNhan)) {
        printf("Loi: Khong the tao ma. Vui long kiem tra lai.\n");
        return;
    }
    printf("Ma benh nhan tu dong tao: %s\n", bn->maBenhNhan);

    printf("Ho ten: ");
    fflush(stdin);
    fgets(bn->hoTen, sizeof(bn->hoTen), stdin);
    bn->hoTen[strcspn(bn->hoTen, "\n")] = 0;

    printf("Gioi tinh (Nam/Nu): ");
    scanf("%s", bn->gioiTinh);

    printf("Ngay sinh (DD/MM/YYYY): ");
    scanf("%s", bn->ngaySinh);

    printf("Can cuoc cong dan: ");
    scanf("%s", bn->canCuocCongDan);

    printf("Ho khau thuong tru: ");
    fflush(stdin);
    fgets(bn->hoKhauThuongTru, sizeof(bn->hoKhauThuongTru), stdin);
    bn->hoKhauThuongTru[strcspn(bn->hoKhauThuongTru, "\n")] = 0;

    printf("So dien thoai: ");
    scanf("%s", bn->soDienThoai);

    int luaChonUuTien;
    printf("Muc do uu tien:\n");
    printf("1. Cap cuu\n");
    printf("2. Thong thuong\n");
    printf("3. Tai kham\n");
    printf("Nhap lua chon (1-3): ");
    scanf("%d", &luaChonUuTien);
    
    switch(luaChonUuTien) {
        case 1:
            strcpy(bn->mucDoUuTien, "Cap cuu");
            break;
        case 2:
            strcpy(bn->mucDoUuTien, "Thong thuong");
            break;
        case 3:
            strcpy(bn->mucDoUuTien, "Tai kham");
            break;
        default:
            strcpy(bn->mucDoUuTien, "Thong thuong");
            break;
    }

    // Lay thoi gian hien tai
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(bn->thoiGianDen, sizeof(bn->thoiGianDen), "%H:%M %d/%m/%Y", info);

    strcpy(bn->trangThai, "Cho kham");
    strcpy(bn->chanDoan, "");

    printf("\nDa them benh nhan: %s (Ma: %s)\n", bn->hoTen, bn->maBenhNhan);
}

// --- HAM SAP XEP DANH SACH CHO KHAM ---
int layGiaTriUuTien(const char* mucDoUuTien) {
    if (strcmp(mucDoUuTien, "Cap cuu") == 0) return 1;
    if (strcmp(mucDoUuTien, "Thong thuong") == 0) return 2;
    if (strcmp(mucDoUuTien, "Tai kham") == 0) return 3;
    return 2; // Mac dinh la thong thuong
}

bool soSanhBenhNhan(const BenhNhan* a, const BenhNhan* b) {
    int uuTienA = layGiaTriUuTien(a->mucDoUuTien);
    int uuTienB = layGiaTriUuTien(b->mucDoUuTien);
    
    if (uuTienA != uuTienB) {
        return uuTienA < uuTienB;
    }
    return strcmp(a->thoiGianDen, b->thoiGianDen) < 0;
}

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

void sapXepDanhSachCho(BenhNhan ds[], int soLuong, int thuatToan) {
    printf("Dang sap xep danh sach cho kham...\n");
    if (thuatToan == 1) {
        printf("Su dung Selection Sort\n");
        selectionSort(ds, soLuong);
    } else {
        printf("Su dung Insertion Sort\n");
        insertionSort(ds, soLuong);
    }
    printf("Sap xep hoan tat!\n");
}

// --- HAM TIM KIEM BENH NHAN ---
void timBenhNhanTheoMa(const char* maCanTim) {
    bool found = false;
    printf("\n--- Ket qua tim kiem benh nhan theo ma '%s' ---\n", maCanTim);
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].maBenhNhan, maCanTim) == 0) {
            hienThiBenhNhan(&danhSachTongHop[i], true);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay benh nhan voi ma '%s'.\n", maCanTim);
    }
}

void timBenhNhanTheoTen(const char* tenCanTim) {
    int countFound = 0;
    printf("\n--- Ket qua tim kiem benh nhan theo ten '%s' ---\n", tenCanTim);
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strstr(danhSachTongHop[i].hoTen, tenCanTim) != NULL) {
            hienThiBenhNhan(&danhSachTongHop[i], true);
            countFound++;
        }
    }
    if (countFound > 0) {
        printf("-> Tim thay %d benh nhan voi ten '%s'.\n", countFound, tenCanTim);
    } else {
        printf("Khong tim thay benh nhan voi ten '%s'.\n", tenCanTim);
    }
}

// --- HAM CAP NHAT TRANG THAI BENH NHAN ---
bool capNhatTrangThaiTheoMa(const char* maBN, const char* trangThaiMoi, const char* chanDoanMoi) {
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].maBenhNhan, maBN) == 0) {
            strcpy(danhSachTongHop[i].trangThai, trangThaiMoi);
            strcpy(danhSachTongHop[i].chanDoan, chanDoanMoi);
            printf("Da cap nhat trang thai benh nhan %s thanh: %s\n", maBN, trangThaiMoi);
            return true;
        }
    }
    printf("Khong tim thay benh nhan co ma: %s\n", maBN);
    return false;
}

// --- MENU QUAN LY HANG DOI KHAM ---
void duaMangVaoQueue(Queue *q, BenhNhan ds[], int soLuong) {
    for (int i = 0; i < soLuong; i++) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Khong the cap phat bo nho cho node moi.\n");
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

int LayBenhNhanDau(Queue *qChoKham, Queue *qDangKham) {
    if (isEmpty(qChoKham)) {
        printf("Hang doi benh nhan cho kham rong.\n");
        return 0;
    }

    Node *p = qChoKham->front;

    if (strcmp(p->data.trangThai, "Cho kham") == 0) {
        printf("\nBenh nhan dang duoc goi kham:\n");
        hienThiBenhNhan(&p->data, false);

        strcpy(p->data.trangThai, "Dang kham");
        printf("Benh nhan %s da chuyen sang trang thai 'Dang kham'.\n", p->data.hoTen);

        // Chuyen benh nhan tu qChoKham sang qDangKham
        qChoKham->front = p->next;
        if (qChoKham->front == NULL) {
            qChoKham->rear = NULL;
        }

        p->next = NULL;
        if (qDangKham->rear == NULL) {
            qDangKham->front = qDangKham->rear = p;
        } else {
            qDangKham->rear->next = p;
            qDangKham->rear = p;
        }
        
        // Cap nhat vao danh sach tong hop
        for (int i = 0; i < soLuongTongHop; i++) {
            if (strcmp(danhSachTongHop[i].maBenhNhan, p->data.maBenhNhan) == 0) {
                strcpy(danhSachTongHop[i].trangThai, "Dang kham");
                break;
            }
        }
        
        return 1;
    } else {
        printf("Benh nhan dau tien trong hang doi khong o trang thai 'Cho kham'.\n");
        return 0;
    }
}

int hoanThanhKhamBenh(Queue *qDangKham, Queue *qHoanThanh) {
    if (isEmpty(qDangKham)) {
        printf("Khong co benh nhan nao dang kham.\n");
        return 0;
    }

    Node *p = qDangKham->front;
    
    printf("\nBenh nhan dang hoan thanh kham:\n");
    hienThiBenhNhan(&p->data, false);

    printf("Nhap chan doan cho benh nhan %s: ", p->data.hoTen);
    fflush(stdin);
    fgets(p->data.chanDoan, sizeof(p->data.chanDoan), stdin);
    p->data.chanDoan[strcspn(p->data.chanDoan, "\n")] = '\0';

    strcpy(p->data.trangThai, "Hoan thanh");
    printf("Benh nhan %s da hoan thanh kham benh.\n", p->data.hoTen);

    // Chuyen benh nhan tu qDangKham sang qHoanThanh
    qDangKham->front = p->next;
    if (qDangKham->front == NULL) {
        qDangKham->rear = NULL;
    }

    p->next = NULL;
    if (qHoanThanh->rear == NULL) {
        qHoanThanh->front = qHoanThanh->rear = p;
    } else {
        qHoanThanh->rear->next = p;
        qHoanThanh->rear = p;
    }
    
    // Cap nhat vao danh sach tong hop
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].maBenhNhan, p->data.maBenhNhan) == 0) {
            strcpy(danhSachTongHop[i].trangThai, "Hoan thanh");
            strcpy(danhSachTongHop[i].chanDoan, p->data.chanDoan);
            break;
        }
    }
    
    return 1;
}

void hienThiQueue(Queue *q, const char* tenQueue) {
    if (isEmpty(q)) {
        printf("Danh sach %s rong.\n", tenQueue);
        return;
    }

    printf("\n=== DANH SACH BENH NHAN TRONG %s ===\n", tenQueue);
    printf("%-4s %-10s %-20s %-8s %-12s %-15s %-15s %-15s %-12s\n",
           "STT", "MaBN", "HoTen", "GioiTinh", "NgaySinh", "SDT", "UuTien", "ThoiGianDen", "TrangThai");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    Node *p = q->front;
    int stt = 1;
    while (p != NULL) {
        printf("%-4d %-10s %-20s %-8s %-12s %-15s %-15s %-15s %-12s\n",
               stt++,
               p->data.maBenhNhan,
               p->data.hoTen,
               p->data.gioiTinh,
               p->data.ngaySinh,
               p->data.soDienThoai,
               p->data.mucDoUuTien,
               p->data.thoiGianDen,
               p->data.trangThai);
        p = p->next;
    }
    printf("-----------------------------------------------------------------------------------------------------------\n");
}

int chuyenQueueSangMang(Queue *q, BenhNhan ds[]) {
    int i = 0;
    Node *p = q->front;
    while (p != NULL) {
        ds[i++] = p->data;
        p = p->next;
    }
    return i;
}

void freeQueue(Queue *q) {
    Node *current = q->front;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

// --- MENU CHINH CUA CHUONG TRINH ---
void menuChinh() {
    int luaChon;
    char maCanTim[10];
    char tenCanTim[50];
    int soLuongQCK = 0, soLuongQDK = 0, soLuongQHT = 0;
    BenhNhan tempDSQCK[100], tempDSQDK[100], tempDSQHT[100];

    // Khoi tao cac Queue
    initQueue(&qChoKham);
    initQueue(&qDangKham);
    initQueue(&qHoanThanh);

    // Doc du lieu tu file khi khoi dong chuong trinh
    docDanhSachTuFile("benhnhan_tonghop.txt", danhSachTongHop, &soLuongTongHop);

    // Phan loai benh nhan vao 3 hang doi
    for (int i = 0; i < soLuongTongHop; i++) {
        if (strcmp(danhSachTongHop[i].trangThai, "Cho kham") == 0) {
            tempDSQCK[soLuongQCK++] = danhSachTongHop[i];
        } else if (strcmp(danhSachTongHop[i].trangThai, "Dang kham") == 0) {
            tempDSQDK[soLuongQDK++] = danhSachTongHop[i];
        } else if (strcmp(danhSachTongHop[i].trangThai, "Hoan thanh") == 0) {
            tempDSQHT[soLuongQHT++] = danhSachTongHop[i];
        }
    }

    // Sap xep danh sach cho kham theo uu tien
    sapXepDanhSachCho(tempDSQCK, soLuongQCK, 1);

    // Dua vao Queue
    duaMangVaoQueue(&qChoKham, tempDSQCK, soLuongQCK);
    duaMangVaoQueue(&qDangKham, tempDSQDK, soLuongQDK);
    duaMangVaoQueue(&qHoanThanh, tempDSQHT, soLuongQHT);

    do {
        printf("\n========== HE THONG QUAN LY KHAM BENH ==========\n");
        printf("1. Them benh nhan moi\n");
        printf("2. Hien thi danh sach cho kham\n");
        printf("3. Hien thi danh sach dang kham\n");
        printf("4. Hien thi danh sach hoan thanh\n");
        printf("5. Goi benh nhan tiep theo\n");
        printf("6. Hoan thanh kham benh\n");
        printf("7. Tim kiem benh nhan theo ma\n");
        printf("8. Tim kiem benh nhan theo ten\n");
        printf("9. Hien thi danh sach tong hop\n");
        printf("10. Sap xep lai danh sach cho kham\n");
        printf("11. Luu du lieu va thoat\n");
        printf("================================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                printf("\n--- THEM BENH NHAN MOI ---\n");
                nhapMotBenhNhan(&danhSachTongHop[soLuongTongHop]);
                
                // Them vao queue cho kham
                Node *newNode = (Node *)malloc(sizeof(Node));
                if (newNode != NULL) {
                    newNode->data = danhSachTongHop[soLuongTongHop];
                    newNode->next = NULL;
                    
                    if (qChoKham.rear == NULL) {
                        qChoKham.front = qChoKham.rear = newNode;
                    } else {
                        qChoKham.rear->next = newNode;
                        qChoKham.rear = newNode;
                    }
                    soLuongTongHop++;
                    printf("Da them benh nhan vao hang doi cho kham.\n");
                }
                break;
                
            case 2:
                printf("\n--- DANH SACH CHO KHAM ---\n");
                hienThiQueue(&qChoKham, "HANG DOI CHO KHAM");
                break;
                
            case 3:
                printf("\n--- DANH SACH DANG KHAM ---\n");
                hienThiQueue(&qDangKham, "HANG DOI DANG KHAM");
                break;
                
            case 4:
                printf("\n--- DANH SACH HOAN THANH ---\n");
                hienThiQueue(&qHoanThanh, "HANG DOI HOAN THANH");
                break;
                
            case 5:
                printf("\n--- GOI BENH NHAN TIEP THEO ---\n");
                LayBenhNhanDau(&qChoKham, &qDangKham);
                break;
                
            case 6:
                printf("\n--- HOAN THANH KHAM BENH ---\n");
                hoanThanhKhamBenh(&qDangKham, &qHoanThanh);
                break;
                
            case 7:
                printf("\n--- TIM KIEM THEO MA ---\n");
                printf("Nhap ma benh nhan can tim: ");
                scanf("%s", maCanTim);
                timBenhNhanTheoMa(maCanTim);
                break;
                
            case 8:
                printf("\n--- TIM KIEM THEO TEN ---\n");
                printf("Nhap ten benh nhan can tim: ");
                fflush(stdin);
                fgets(tenCanTim, sizeof(tenCanTim), stdin);
                tenCanTim[strcspn(tenCanTim, "\n")] = '\0';
                timBenhNhanTheoTen(tenCanTim);
                break;
                
            case 9:
                printf("\n--- DANH SACH TONG HOP ---\n");
                hienThiDanhSachTongHop(danhSachTongHop, soLuongTongHop);
                break;
                
            case 10:
                printf("\n--- SAP XEP LAI DANH SACH CHO KHAM ---\n");
                soLuongQCK = chuyenQueueSangMang(&qChoKham, tempDSQCK);
                freeQueue(&qChoKham);
                initQueue(&qChoKham);
                
                printf("Chon thuat toan sap xep (1-Selection Sort, 2-Insertion Sort): ");
                int thuatToan;
                scanf("%d", &thuatToan);
                sapXepDanhSachCho(tempDSQCK, soLuongQCK, thuatToan);
                duaMangVaoQueue(&qChoKham, tempDSQCK, soLuongQCK);
                printf("Da sap xep lai danh sach cho kham.\n");
                break;
                
            case 11:
                printf("\n--- LUU DU LIEU VA THOAT ---\n");
                ghiDanhSachVaoFile("benhnhan_tonghop.txt", danhSachTongHop, soLuongTongHop);
                
                soLuongQCK = chuyenQueueSangMang(&qChoKham, tempDSQCK);
                ghiDanhSachVaoFile("benhnhan_chokham.txt", tempDSQCK, soLuongQCK);
                
                soLuongQDK = chuyenQueueSangMang(&qDangKham, tempDSQDK);
                ghiDanhSachVaoFile("benhnhan_dangkham.txt", tempDSQDK, soLuongQDK);
                
                soLuongQHT = chuyenQueueSangMang(&qHoanThanh, tempDSQHT);
                ghiDanhSachVaoFile("benhnhan_hoanthanh.txt", tempDSQHT, soLuongQHT);
                
                printf("Da luu du lieu thanh cong!\n");
                break;
                
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    } while (luaChon != 11);

    // Giai phong bo nho
    freeQueue(&qChoKham);
    freeQueue(&qDangKham);
    freeQueue(&qHoanThanh);
    
    printf("Cam on ban da su dung he thong!\n");
}

// --- HAM MAIN ---
int main() {
    menuChinh();
    return 0;
}
