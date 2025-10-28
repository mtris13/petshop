/* Service Repository - Quản lý CRUD cho dịch vụ SPA
 *
 * File format: services.txt
 * Format: id|name|description|price|duration
 * Example: SP001|Basic Spa|Relaxing spa treatment|200000|60
 */

#pragma once
#include "domain/entities/Service.hpp"
#include "ds/LinkedList.hpp"
#include <fstream>
#include <sstream>
#include <string>

class ServiceRepository {
private:
  const string serviceFilePath = "../data/services.txt";
  const string invalid = "";

  // Helper: đọc một dòng dữ liệu theo serviceId
  string readingFile(const string &serviceId);

  // Helper: ghi/cập nhật một dòng dữ liệu
  void writingFile(const string &serviceId, const string &writeLine);

public:
  ServiceRepository() {}

  // ===== GET Operations =====

  // Lấy thông tin đầy đủ của một service
  Service getServiceInfo(const string &serviceId);

  // Lấy danh sách tất cả services spa
  LinkedList<Service> getAllServices();

  // Lấy giá của service
  float getServicePrice(const string &serviceId);

  // Lấy thời gian thực hiện
  int getServiceDuration(const string &serviceId);

  // ===== SET Operations =====

  // Thêm hoặc cập nhật service
  void setServiceInfo(const Service &service);

  // Cập nhật giá
  void updatePrice(const string &serviceId, float newPrice);

  // ===== CHECK Operations =====

  // Kiểm tra serviceId có tồn tại không
  bool isValidServiceId(const string &serviceId);

  // ===== DELETE Operation =====

  // Xóa vĩnh viễn khỏi file
  void deleteService(const string &serviceId);

  // ===== SEARCH Operations =====

  // Tìm kiếm service theo tên (partial match)
  LinkedList<Service> searchByName(const string &keyword);

  // Tìm services trong khoảng giá
  LinkedList<Service> searchByPriceRange(float minPrice, float maxPrice);

  // Đếm tổng số services
  int countServices();
};