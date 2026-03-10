import Foundation

struct PaymentService {
    func pay(order: DeliveryOrder, cardLast4: String) async throws -> String {
        try await Task.sleep(nanoseconds: 800_000_000)

        guard cardLast4.count == 4 else {
            throw NSError(domain: "Payment", code: 400, userInfo: [NSLocalizedDescriptionKey: "Invalid card data."])
        }

        return "\(order.paymentProvider.rawValue)-\(Int.random(in: 100000...999999))"
    }
}
