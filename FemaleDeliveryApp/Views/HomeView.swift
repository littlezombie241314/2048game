import SwiftUI

struct HomeView: View {
    @EnvironmentObject private var authViewModel: AuthViewModel
    @EnvironmentObject private var orderViewModel: OrderViewModel

    var body: some View {
        NavigationStack {
            VStack(spacing: 16) {
                if let user = authViewModel.currentUser {
                    VStack(alignment: .leading, spacing: 8) {
                        Text("Welcome, \(user.fullName)")
                            .font(.title3).bold()
                        Text("Country: \(user.country.displayName)")
                        Text("Platform: \(user.platform.displayName)")
                        Text("Identity: Female verified")
                            .foregroundStyle(.green)
                    }
                    .frame(maxWidth: .infinity, alignment: .leading)
                    .padding()
                    .background(.thinMaterial)
                    .clipShape(RoundedRectangle(cornerRadius: 12))
                }

                NavigationLink("Create Delivery Order") {
                    CreateOrderView()
                }
                .buttonStyle(.borderedProminent)

                List(orderViewModel.orders) { order in
                    VStack(alignment: .leading, spacing: 6) {
                        Text("\(order.pickupAddress) → \(order.dropoffAddress)")
                            .font(.subheadline).bold()
                        Text("Package: \(order.packageDescription)")
                        Text("Payment: \(order.paymentProvider.rawValue)")
                        Text("Fee: $\(order.estimatedFeeUSD.description)")
                        Text(order.isPaid ? "Paid" : "Awaiting payment")
                            .foregroundStyle(order.isPaid ? .green : .orange)
                    }
                }

                Button("Sign Out") {
                    authViewModel.signOut()
                }
            }
            .padding()
            .navigationTitle("Female Delivery")
        }
    }
}
