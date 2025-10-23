#include "infra/repositories/BookingRepoFile.hpp"

// ===== Private Helper Methods =====

string BookingRepository::readingFile(const string &bookingId) {
  ifstream file(bookingFilePath);
  if (!file.is_open()) {
    cerr << "Error: Cannot open file " << bookingFilePath << '\n';
    return invalid;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    string id;
    getline(ss, id, '|');

    if (id == bookingId) {
      file.close();
      return line;
    }
  }

  file.close();
  return invalid;
}

void BookingRepository::writingFile(const string &bookingId,
                                    const string &writeLine) {
  const string tempPath = "../data/temp.txt";

  ifstream in(bookingFilePath);
  bool originalFileExisted = in.is_open();

  ofstream out(tempPath);
  if (!out.is_open()) {
    cerr << "Error: Cannot create temp file " << tempPath << '\n';
    if (originalFileExisted)
      in.close();
    return;
  }

  string line;
  bool foundAndUpdated = false;

  if (originalFileExisted) {
    while (getline(in, line)) {
      if (line.empty())
        continue;

      stringstream ss(line);
      string id;
      getline(ss, id, '|');

      if (id == bookingId) {
        out << writeLine << '\n';
        foundAndUpdated = true;
      } else {
        out << line << '\n';
      }
    }
  }

  if (!foundAndUpdated) {
    out << writeLine << '\n';
  }

  if (originalFileExisted)
    in.close();
  out.close();

  if (originalFileExisted && remove(bookingFilePath.c_str()) != 0) {
    cerr << "Error: Could not remove original file " << bookingFilePath << '\n';
  }

  if (rename(tempPath.c_str(), bookingFilePath.c_str()) != 0) {
    cerr << "Error: Could not rename temp file to " << bookingFilePath << '\n';
  }
}

// ===== GET Operations =====

Booking BookingRepository::getBookingInfo(const string &bookingId) {
  Booking booking;
  string info = readingFile(bookingId);

  if (info == invalid)
    return booking;

  string id, clientId, petId, serviceId, date, time, status;
  stringstream ss(info);

  getline(ss, id, '|');
  getline(ss, clientId, '|');
  getline(ss, petId, '|');
  getline(ss, serviceId, '|');
  getline(ss, date, '|');
  getline(ss, time, '|');
  getline(ss, status, '|');

  booking = Booking(id, clientId, petId, serviceId, date, time, status);
  return booking;
}

LinkedList<Booking> BookingRepository::getAllBookings() {
  LinkedList<Booking> bookings;
  ifstream file(bookingFilePath);

  if (!file.is_open()) {
    cerr << "Error: Cannot open file " << bookingFilePath << '\n';
    return bookings;
  }

  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    string id, clientId, petId, serviceId, date, time, status;

    getline(ss, id, '|');
    getline(ss, clientId, '|');
    getline(ss, petId, '|');
    getline(ss, serviceId, '|');
    getline(ss, date, '|');
    getline(ss, time, '|');
    getline(ss, status, '|');

    Booking booking(id, clientId, petId, serviceId, date, time, status);
    bookings.pushBack(booking);
  }

  file.close();
  return bookings;
}

LinkedList<Booking>
BookingRepository::getBookingsByClient(const string &clientId) {
  LinkedList<Booking> results;
  LinkedList<Booking> allBookings = getAllBookings();

  Node<Booking> *current = allBookings.getHead();
  while (current != nullptr) {
    if (current->getData().getClientId() == clientId) {
      results.pushBack(current->getData());
    }
    current = current->getNext();
  }

  return results;
}

LinkedList<Booking> BookingRepository::getBookingsByDate(const string &date) {
  LinkedList<Booking> results;
  LinkedList<Booking> allBookings = getAllBookings();

  Node<Booking> *current = allBookings.getHead();
  while (current != nullptr) {
    if (current->getData().getDate() == date) {
      results.pushBack(current->getData());
    }
    current = current->getNext();
  }

  return results;
}

LinkedList<Booking>
BookingRepository::getBookingsByStatus(const string &status) {
  LinkedList<Booking> results;
  LinkedList<Booking> allBookings = getAllBookings();

  Node<Booking> *current = allBookings.getHead();
  while (current != nullptr) {
    if (current->getData().getStatus() == status) {
      results.pushBack(current->getData());
    }
    current = current->getNext();
  }

  return results;
}

// ===== SET Operations =====

void BookingRepository::createBooking(const Booking &booking) {
  string line = booking.getBookingId() + "|" + booking.getClientId() + "|" +
                booking.getPetId() + "|" + booking.getServiceId() + "|" +
                booking.getDate() + "|" + booking.getTime() + "|" +
                booking.getStatus();

  writingFile(booking.getBookingId(), line);
}

void BookingRepository::updateStatus(const string &bookingId,
                                     const string &newStatus) {
  Booking booking = getBookingInfo(bookingId);
  if (booking.getBookingId().empty()) {
    cerr << "Error: Booking not found " << bookingId << '\n';
    return;
  }

  booking.setStatus(newStatus);
  createBooking(booking); // reuse create method for update
}

void BookingRepository::updateBooking(const Booking &booking) {
  createBooking(booking);
}

// ===== CHECK Operations =====

bool BookingRepository::isValidBookingId(const string &bookingId) {
  string info = readingFile(bookingId);
  return (info != invalid);
}

bool BookingRepository::isTimeSlotAvailable(const string &date,
                                            const string &time) {
  LinkedList<Booking> bookingsOnDate = getBookingsByDate(date);

  Node<Booking> *current = bookingsOnDate.getHead();
  while (current != nullptr) {
    Booking booking = current->getData();
    // Chỉ kiểm tra các booking chưa bị hủy
    if (booking.getTime() == time && booking.getStatus() != "Cancelled") {
      return false; // Đã có booking vào thời gian này
    }
    current = current->getNext();
  }

  return true; // Thời gian còn trống
}

// ===== DELETE Operation =====

void BookingRepository::deleteBooking(const string &bookingId) {
  const string tempPath = "../data/temp.txt";

  ifstream in(bookingFilePath);
  ofstream out(tempPath);

  if (!in.is_open() || !out.is_open()) {
    cerr << "Error opening files for removal.\n";
    in.close();
    out.close();
    return;
  }

  string line;
  bool removed = false;

  while (getline(in, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    string id;
    getline(ss, id, '|');

    if (id == bookingId) {
      removed = true;
    } else {
      out << line << '\n';
    }
  }

  in.close();
  out.close();

  if (removed) {
    remove(bookingFilePath.c_str());
    rename(tempPath.c_str(), bookingFilePath.c_str());
  } else {
    remove(tempPath.c_str());
  }
}

// ===== UTILITY =====

string BookingRepository::generateBookingId() {
  LinkedList<Booking> allBookings = getAllBookings();
  int maxNum = 0;

  Node<Booking> *current = allBookings.getHead();
  while (current != nullptr) {
    string id = current->getData().getBookingId();
    if (id.length() >= 2 && id.substr(0, 2) == "BK") {
      int num = stoi(id.substr(2));
      if (num > maxNum) {
        maxNum = num;
      }
    }
    current = current->getNext();
  }

  // Tạo ID mới
  maxNum++;
  string newId = "BK";
  if (maxNum < 10)
    newId += "00";
  else if (maxNum < 100)
    newId += "0";
  newId += to_string(maxNum);

  return newId;
}

int BookingRepository::countBookings() {
  LinkedList<Booking> allBookings = getAllBookings();
  return allBookings.getSize();
}

int BookingRepository::countBookingsByStatus(const string &status) {
  LinkedList<Booking> bookings = getBookingsByStatus(status);
  return bookings.getSize();
}