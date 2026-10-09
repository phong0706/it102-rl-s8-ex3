#include <stdio.h>

struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;      // 1: Free, 2: Personal, 3: Family
    int days_overdue;
    int active_devices;
};

int main() {
    int n;
    int i;
    int total_revenue = 0;
    int downgraded_count = 0;

    // 1. Nh?p và ki?m soát s? lu?ng tài kho?n N
    do {
        printf("Nhap so luong tai khoan N (1 <= N <= 100): ");
        if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
            printf("[LOHI] So luong tai khoan khong hop le! Vui long nhap lai.\n");
            while (getchar() != '\n'); // Xoa bo dem nhap
        } else {
            break;
        }
    } while (1);

    struct UserAccount user_list[100];

    // 2. Nh?p thông tin chi ti?t t?ng tài kho?n kèm validation
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin cho tai khoan thu %d ---\n", i + 1);
        
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &user_list[i].user_id);

        printf("Ten tai khoan (username): ");
        scanf("%s", user_list[i].username);

        // Validation cho plan_type [1, 3]
        do {
            printf("Loai goi hien tai (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &user_list[i].plan_type);
            if (user_list[i].plan_type < 1 || user_list[i].plan_type > 3) {
                printf("[LOI] Loai goi khong hop le (chi nhan tu 1 den 3). Nhap lai!\n");
            } else {
                break;
            }
        } while (1);

        // Validation cho days_overdue >= 0
        do {
            printf("So ngay no cuoc (days_overdue >= 0): ");
            scanf("%d", &user_list[i].days_overdue);
            if (user_list[i].days_overdue < 0) {
                printf("[LOI] So ngay no cuoc khong the am. Nhap lai!\n");
            } else {
                break;
            }
        } while (1);

        // Validation cho active_devices > 0
        do {
            printf("So thiet bi dang ket noi (active_devices > 0): ");
            scanf("%d", &user_list[i].active_devices);
            if (user_list[i].active_devices <= 0) {
                printf("[LOI] So thiet bi phai lon hon 0. Nhap lai!\n");
            } else {
                break;
            }
        } while (1);
    }

    // M?ng luu chi phí th?c thu c?a t?ng tài kho?n sau khi x? lý
    int final_fee[100];

    // 3. Quy t?c X? lý T? d?ng & Tính toán Doanh thu
    for (i = 0; i < n; i++) {
        // Quy t?c 1: H? c?p do n? cu?c (days_overdue >= 3)
        if (user_list[i].days_overdue >= 3) {
            if (user_list[i].plan_type != 1) {
                downgraded_count++;
            }
            user_list[i].plan_type = 1; // Ðua v? gói Free
            final_fee[i] = 0;           // Phí b?ng 0 VNÐ
        } else {
            // Quy t?c 2: N?u không b? h? c?p, tính phí theo gói hi?n t?i
            if (user_list[i].plan_type == 1) {
                final_fee[i] = 0;
            } else if (user_list[i].plan_type == 2) {
                // Gói Personal: Phí co b?n 120,000 VND + ph? thu thi?t b? vu?t quá 1
                int base_fee = 120000;
                int surcharge = 0;
                if (user_list[i].active_devices > 1) {
                    surcharge = (user_list[i].active_devices - 1) * 30000;
                }
                final_fee[i] = base_fee + surcharge;
            } else if (user_list[i].plan_type == 3) {
                // Gói Family: Phí co b?n 250,000 VND (cho phép t?i da 5 thi?t b?)
                final_fee[i] = 250000;
            }
        }
        total_revenue += final_fee[i];
    }

    // 4. Xu?t Báo cáo K?t qu?
    printf("\n\n=========================================================================\n");
    printf("                  BAO CAO DOI SOAT & XU LY NO CUOC SAAS                   \n");
    printf("=========================================================================\n");
    printf("%-8s %-15s %-10s %-12s %-10s %-18s\n", "MA TK", "TEN TK", "MA GOI", "THI?T B?", "N? (NGÀY)", "PHÍ TH?C THU (VNÐ)");
    printf("-------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-8d %-15s %-10d %-12d %-10d %-18d\n",
               user_list[i].user_id,
               user_list[i].username,
               user_list[i].plan_type,
               user_list[i].active_devices,
               user_list[i].days_overdue,
               final_fee[i]);
    }

    printf("-------------------------------------------------------------------------\n");
    printf("THONG KE TONG KET:\n");
    printf("- Tong doanh thu thuc te thu duoc trong ky : %d VNÐ\n", total_revenue);
    printf("- Tong so tai kho?n b? h? c?p v? gói Free : %d tai khoan\n", downgraded_count);
    printf("=========================================================================\n");

    return 0;
}
